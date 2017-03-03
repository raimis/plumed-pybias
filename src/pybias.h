/*
Copyright (c) 2017 Raimondas Galvelis
*/

#ifndef __PYBIAS_H
#define __PYBIAS_H

#include <Python.h>
#include <plumed/bias/Bias.h>

namespace PLMD::bias
{
  class PyBias: public Bias
  {
    std::vector<Value*> args; // Extra arguments

    PyObject* function; // Python function object

    PyObject* input; // Numpy array for input values
    PyObject* force; // Numpy array for bias forces
    PyObject* extra; // Numpy array for extra values

  public:
    static void registerKeywords(Keywords&);
    explicit PyBias(const ActionOptions&);
    ~PyBias();
    void calculate();
    unsigned getNumberOfExtraArguments() const;
  };
}

#endif
