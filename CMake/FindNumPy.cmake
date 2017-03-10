# Copyright (c) 2017 Raimondas Galvelis

find_package(PythonInterp REQUIRED)

execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "
from __future__ import print_function
import numpy
print(numpy.get_include())"
                OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "
from __future__ import print_function
import numpy
print(numpy.__version__)"
                OUTPUT_VARIABLE NUMPY_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NumPy
                                  REQUIRED_VARS NUMPY_INCLUDE_DIR
                                  VERSION_VAR NUMPY_VERSION)

