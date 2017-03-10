# Copyright (c) 2017 Raimondas Galvelis

find_package(PythonInterp REQUIRED)

execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "
from __future__ import print_function
import mpi4py
print(mpi4py.get_include())"
                OUTPUT_VARIABLE MPI4PY_INCLUDE_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "
from __future__ import print_function
import mpi4py
print(mpi4py.__version__)"
                OUTPUT_VARIABLE MPI4PY_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MPI4Py
                                  REQUIRED_VARS MPI4PY_INCLUDE_DIR
                                  VERSION_VAR MPI4PY_VERSION)

