/*
Copyright (c) 2017 Raimondas Galvelis
*/

#include "pybias.h"
#include "pybias_plumed.h"

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
    return PyInt_FromLong(action->getStep());
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
    return PyInt_FromLong(bias->getNumberOfArguments());
  }

  // Implementation of plumed.getNumExArgs
  static PyObject* getNumExArgs(PyObject* self, PyObject* args)
  {
    plumed_assert(action);
    PyBias *bias = dynamic_cast<PyBias*>(action);
    plumed_assert(bias);
    return PyInt_FromLong(bias->getNumberOfExtraArguments());
  }

  // Python functions
  static PyMethodDef functions[] = {
    {"getStep", getStep, METH_NOARGS, NULL},
    {"getComm", getComm, METH_NOARGS, NULL},
    {"getMultiSimComm", getMultiSimComm, METH_NOARGS, NULL},
    {"getKbT", getKbT, METH_NOARGS, NULL},
    {"getNumArgs", getNumArgs, METH_NOARGS, NULL},
    {"getNumExArgs", getNumExArgs, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
  };

  void initModule()
  {
    // Import mpi4py C-API
    plumed_massert(!import_mpi4py(), "mpi4py C-API import failed");

    // Initialize the built-in module
    plumed_assert(Py_InitModule("plumed", functions));
  }

  void setAction(Action* action_)
  {
    plumed_assert(action_);
    action = action_;
  }

}}
