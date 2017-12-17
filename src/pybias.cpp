/*
Copyright (c) 2017 Raimondas Galvelis
*/

#include "pybias.h"
#include "pybias_plumed.h"

#include <bytesobject.h> // Remove after finish support for Python 2

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/ndarrayobject.h>
#include <numpy/npy_math.h>

#include <plumed/bias/ActionRegister.h>

#include <link.h>
#include <string>
#include <dlfcn.h>

using namespace std;

namespace PLMD{
namespace bias{

  PLUMED_REGISTER_ACTION(PyBias, "PYBIAS")

  void PyBias::registerKeywords(Keywords& keys)
  {
    Bias::registerKeywords(keys);
    keys.use("ARG");
    keys.add("compulsory", "FILE", "bias.py",
             "the name of a file containing a python scrip.");
    keys.add("optional", "EXTRA",
             "extra argument");
    // HACK fix for PLUMED 2.3.x, remove after finish support for 2.2.x
    if (!keys.outputComponentExists("bias", false))
    {
      componentsAreNotOptional(keys);
      keys.addOutputComponent("bias", "default", "bias");
    }
  }


  // Callback function for dl_iterate_phdr
  int callback(dl_phdr_info* info, size_t size, void* path_)
  {
    string path = info->dlpi_name;

    if (path.size() == 0) return 0;
    size_t i = path.rfind("/");
    if (i == string::npos) return 0;
    if (path.substr(i+1).find("libpython") == string::npos) return 0;

    *(string*)path_ = path;

    return 0;
  }

  #if PY_MAJOR_VERSION < 3
  void import_array_wrapper()
#else
  int import_array_wrapper()
#endif
  {
    import_array();
  }

  PyBias::PyBias(const ActionOptions& ao):
  PLUMED_BIAS_INIT(ao),
  args(0)
  {
    // Parse EXTRA keyword for extra arguments
    if (keywords.exists("EXTRA"))
    {
      parseArgumentList("EXTRA", args);
      log.printf("  with extra arguments");
      for (unsigned i=0; i<args.size(); i++)
      {
        addDependency(args[i]->getPntrToAction());
        log.printf(" %s", args[i]->getName().c_str());
      }
      log.printf("\n");
    }

    //if (!Py_IsInitialized())
    //{
#if PY_MAJOR_VERSION > 2
      // Add a built-in module
      plumed_assert(!PyImport_AppendInittab("plumed", PyInit_plumed));
#endif

      //Initialize Python interpreter
      Py_Initialize();

      // Import numpy C-API
      import_array_wrapper();

#if PY_MAJOR_VERSION < 3
      // Initialize the built-in module
      initModule();
#endif
    //}

    // Get Python library name
    string PyLibPath;
    plumed_assert(!dl_iterate_phdr(callback, (void*)&PyLibPath));

    // Reload Python library globally
    // Solve the problem with "math" module loading
    // Cannot use DLLLoader, it loads with RTLD_LOCAL flag
    void* handle = dlopen(PyLibPath.c_str(), RTLD_NOW|RTLD_GLOBAL);
    if (!handle)
      plumed_merror(dlerror()); // plumed_massert does not work here!
    link_map *map;
    if (dlinfo(handle, RTLD_DI_LINKMAP, &map))
      plumed_merror(dlerror()); // plumed_massert does not work here!
    log.printf("  using Python %s %s\n", Py_GetVersion(), map->l_name);

    // Import Numpy
    PyObject* module = PyImport_ImportModule("numpy"); // New reference
    if (!module)
    {
      PyErr_Print();
      plumed_merror("numpy import failed. See for an error message above");
    }
    PyObject* version = PyObject_GetAttrString(module, "__version__"); // New reference
    plumed_assert(version);
    PyObject* str = PyObject_Str(module); // New reference
    plumed_assert(str);
    Py_DECREF(module);
    log.printf("  using numpy %s %s\n", PyBytes_AsString(version),
               PyBytes_AsString(str));
    Py_DECREF(version);
    Py_DECREF(str);

    // Import mpi4py
    module = PyImport_ImportModule("mpi4py"); // New reference
    if (!module)
    {
      PyErr_Print();
      plumed_merror("mpi4py import failed. See for an error message above");
    }
    version = PyObject_GetAttrString(module, "__version__"); // New reference
    plumed_assert(version);
    str = PyObject_Str(module); // New reference
    plumed_assert(str);
    Py_DECREF(module);
    log.printf("  using mpi4py %s %s\n", PyBytes_AsString(version),
               PyBytes_AsString(str));
    Py_DECREF(version);
    Py_DECREF(str);

    // Parse FILE and NAME keywords
    string filename, funcname;
    parse("FILE", filename);
    log.printf("  using Python script %s\n", filename.c_str());

    // Check if all keywords have been read
    checkRead();

    // Set the context of the module
    setAction(this);

    // Run the Python script
    FILE* fp = fopen(filename.c_str(), "r");
    plumed_massert(!PyRun_SimpleFile(fp, filename.c_str()),
                   "Python script failed. See for an error message above");
    fclose(fp);

    // Extract the Python function
    PyObject* main = PyImport_AddModule("__main__");
    plumed_assert(main);
    function = PyObject_GetAttrString(main, "bias"); // New reference
    plumed_massert(function, "Cannot find the Python function in the file");
    plumed_massert(PyCallable_Check(function),
                   "The Python function is not callable");

    // Allocate the Numpy arrays
    npy_intp dims[1];
    dims[0] = getNumberOfArguments();
    input = PyArray_SimpleNew(1, &dims[0], NPY_DOUBLE); // New reference
    plumed_assert(input);
    force = PyArray_SimpleNew(1, &dims[0], NPY_DOUBLE); // New reference
    plumed_assert(force);
    dims[0] = args.size();
    extra = PyArray_SimpleNew(1, &dims[0], NPY_DOUBLE); // New reference
    plumed_assert(extra);

    // Setup components
    // HACK fix for PLUMED 2.3.x, remove after finish support for 2.2.x
    if (getNumberOfComponents() == 0)
    {
      addComponent("bias");
      componentIsNotPeriodic("bias");
    }

  }

  PyBias::~PyBias()
  {
    // Deallocate the Python objects
    Py_DECREF(function);
    Py_DECREF(input);
    Py_DECREF(force);
    Py_DECREF(extra);

    // Finalize the Python interpreter
    Py_Finalize();
  }

  void PyBias::calculate()
  {
    // Fill the Numpy arrays with the input values and NaNs
    for (npy_intp i=0; i<getNumberOfArguments(); i++)
    {
      *(npy_double*)PyArray_GETPTR1((PyArrayObject*)input, i) = getArgument(i);
      *(npy_double*)PyArray_GETPTR1((PyArrayObject*)force, i) = NPY_NAN;
    }

    // Fill the Numpy array with extra values
    for (npy_intp i=0; i<(npy_intp)args.size(); i++)
      *(npy_double*)PyArray_GETPTR1((PyArrayObject*)extra, i) = args[i]->get();

    // Set the action pointer
    setAction(this);

    // Call the Python function
    PyObject* bias = PyObject_CallFunctionObjArgs(function, input, force, extra,
                                                  NULL); // New reference
    if (!bias)
    {
      PyErr_Print();
      plumed_merror("The Python function failed. See for an error message above");
    }

    // Process the Python function result
    plumed_massert(PyFloat_Check(bias), "The Python function has to return a Python float");
    getPntrToComponent(0)->set(PyFloat_AS_DOUBLE(bias));
    Py_DECREF(bias);

    // Process the force array
    for (npy_intp i=0; i<getNumberOfArguments(); i++)
    {
      double f = *(npy_double*)PyArray_GETPTR1((PyArrayObject*)force, i);
      plumed_massert(!npy_isnan(f), "The force array contains a NaN value");
      setOutputForce(i, f);
    }
  }

  unsigned PyBias::getNumberOfExtraArguments() const
  {
    return args.size();
  }

}}
