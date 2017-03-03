/*
Copyright (c) 2017 Raimondas Galvelis
*/

#ifndef __PYBIAS_PLUMED_H
#define __PYBIAS_PLUMED_H

#include <plumed/bias/Bias.h>

namespace PLMD{
namespace bias{

  // Initialize the Python module
  void initModule();

  // Set context for the Python module
  void setAction(Action*);

}}

#endif
