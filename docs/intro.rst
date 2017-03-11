Introduction
============

**This project is still under construction!**

*PyBias* is a `PLUMED <http://www.plumed.org/>`__ plug-in with an
embedded `Python <http://www.python.org/>`__ interpreter. It is intended
for a quick prototyping of enhanced sampling methods. The goal of
*PyBias* is bridge the gap between *PLUMED* and *Python*.

*PLUMED* is a library for free energy calculations with molecular
dynamics (MD). The calculations can be performed as a function of
various collective variables (CV), using state-of-the-art enhanced
sampling methods: metadynamics, parallel-bias metadynamics, *etc.*
*PLUMED* works with `most MD
engines <http://www.plumed.org/md-engines>`__.

*Python* environment has a variety of high-quality numerical algorithm
(`NumPy <http://www.numpy.org/>`__, `SciPy <http://www.scipy.org/>`__,
`SimPy <http://www.sympy.org/>`__, *etc.*) and machine learning
(`scikit-learn <http://scikit-learn.org/>`__,
`Theano <http://www.deeplearning.net/software/theano/>`__,
`TensorFlow <http://www.tensorflow.org/>`__, *etc.*) libraries, which
can be used to compute bias.

Key Features
------------

-  Can use a system or custom *Python* interpreter
-  All installed *Python* modules can be used
-  A built-in *Python* module to access data from *PLUMED*
-  No *PLUMED* re-compilation required

Quick Installation
------------------

If your are lucky (*i.e.* your system has all dependencies), it is just
a 5-step process:

.. code:: bash

    git clone https://github.com/raimis/plumed-pybias.git
    cd plumed-pybias
    cmake . -DCMAKE_INSTALL_PREFIX=~/opt/pybias
    make
    make install

Working Example
---------------

**This is not yet functional!**

.. code:: bash

    # plumed.dat

    # Load PyBias plug-in
    LOAD FILE=libpybias.so

    # Create a collective variable
    dist: DISTANCE ATOMS=1,2

    # Creat a PyBias action, which executes "bias.py"
    PYBIAS ARG=dist

    ENDPLUMED

.. code:: python

    # bias.py

    def bias(coord, force, extra):
        force[:] = 0.
        return 0.

License
-------

*PyBias* is released under `GNU Lesser General Public
License <https://www.gnu.org/licenses/lgpl-3.0-standalone.html>`__ (LGPL
v3).
