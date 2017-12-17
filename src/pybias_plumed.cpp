/*
Copyright (c) 2017 Raimondas Galvelis
*/

#include "pybias.h"
#include "pybias_plumed.h"

//#define PY_ARRAY_UNIQUE_SYMBOL plumed_ARRAY_API
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
//#include <numpy/ndarrayobject.h>

#include <mpi4py/mpi4py.h>

#include <plumed/core/Atoms.h>
#include <plumed/core/PlumedMain.h>
#include <plumed/tools/Communicator.h>

namespace PLMD{
namespace bias{

  // Pointer to the currecnt action
  static Action* action = NULL;

  // Implementation of plumed.getStep
  static PyObject* getStep(PyObject* self, PyObject* args)
  {
    plumed_assert(action);
    return PyLong_FromLong(action->getStep());
  }

  // Implementation of plumed.getComm
  static PyObject* getComm(PyObject* self, PyObject* args)
  {
    plumed_assert(action);
    return PyMPIComm_New(action->comm.Get_comm());
  }

  // Implementation of plumed.getMultiSimComm
  static PyObject* getMultiSimComm(PyObject* self, PyObject* args)
  {
    plumed_assert(action);
    return PyMPIComm_New(action->multi_sim_comm.Get_comm());
  }

  // Implementation of plumed.getKbT
  static PyObject* getKbT(PyObject* self, PyObject* args)
  {
    plumed_assert(action);
    return PyFloat_FromDouble(action->plumed.getAtoms().getKbT());
  }

  // Implementation of plumed.getNumArgs
  static PyObject* getNumArgs(PyObject* self, PyObject* args)
  {
    plumed_assert(action);
    Bias *bias = dynamic_cast<Bias*>(action);
    plumed_assert(bias);
    return PyLong_FromLong(bias->getNumberOfArguments());
  }

  // Implementation of plumed.getNumExArgs
  static PyObject* getNumExArgs(PyObject* self, PyObject* args)
  {
    plumed_assert(action);
    PyBias *bias = dynamic_cast<PyBias*>(action);
    plumed_assert(bias);
    return PyLong_FromLong(bias->getNumberOfExtraArguments());
  }

  // Python module function definitions
  static PyMethodDef functionDefinitions[] = {
    {"getStep", getStep, METH_NOARGS, NULL},
    {"getComm", getComm, METH_NOARGS, NULL},
    {"getMultiSimComm", getMultiSimComm, METH_NOARGS, NULL},
    {"getKbT", getKbT, METH_NOARGS, NULL},
    {"getNumArgs", getNumArgs, METH_NOARGS, NULL},
    {"getNumExArgs", getNumExArgs, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
  };

#if PY_MAJOR_VERSION < 3
  void initModule()
#else

  // Python module definition
  static struct PyModuleDef moduleDefinition = {
    PyModuleDef_HEAD_INIT,
    "plumed",
    NULL,
    -1,
    functionDefinitions,
    NULL,
    NULL,
    NULL,
    NULL
  };

  PyMODINIT_FUNC PyInit_plumed()
#endif
  {
    // Import numpy C-API
    //import_array();

    // Import MPI4Py C-API
    plumed_massert(!import_mpi4py(), "MPI4Py C-API import failed");

    // Initialize the built-in module
#if PY_MAJOR_VERSION < 3
    plumed_assert(Py_InitModule("plumed", functionDefinitions));
#else
    return PyModule_Create(&moduleDefinition);
#endif
  }

  void setAction(Action* action_)
  {
    plumed_assert(action_);
    action = action_;
  }

}}
