/*
Copyright (c) 2017 Raimondas Galvelis
*/

#ifndef __PYBIAS_PLUMED_H
#define __PYBIAS_PLUMED_H

#include <Python.h>
#include <plumed/bias/Bias.h>

namespace PLMD{
namespace bias{

  // Initialize the Python module
#if PY_MAJOR_VERSION < 3
  void initModule();
#else
  PyMODINIT_FUNC PyInit_plumed();
#endif

  // Set context for the Python module
  void setAction(Action*);

}}

#endif
