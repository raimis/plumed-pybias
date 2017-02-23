
**The project is still under construction!**

.. image:: https://travis-ci.org/raimis/plumed-pybias.svg?branch=master
      :target: https://travis-ci.org/raimis/plumed-pybias

.. image:: https://readthedocs.org/projects/plumed-pybias/badge/?version=latest
      :target: http://plumed-pybias.readthedocs.io/en/latest

Introduction
============

*PyBias* is a *PLUMED* plug-in with an embeded *Python* interpreter.

Key Features
------------

* All system *Python* modules can be used inside
* Built-in module to access information from PLUMED
* No PLUMED re-compilation needed

Simple Example
--------------

.. code-block:: bash

   # plumed.dat

   LOAD FILE=libpybias.so

   d: DISTANCE ATOMS=1,2

   PYBIAS ARG=d

.. code-block::

  # bias.py

  import numpy as py

  def bias(position, force):

      force[:] = 0.

      return 0.


Quick Installation
------------------

If your are lucky (*i.e.* your system already has all dependencies), it is just
a 5-step process::

   git clone https://github.com/raimis/plumed-pybias.git
   cd plumed-pybias
   cmake .
   make
   make install

Licence and Citation
--------------------

LGPL-3.0

