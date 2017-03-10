# Copyright (c) 2017 Raimondas Galvelis

# Find PLUMED
find_package(PLUMED REQUIRED)
include_directories(${PLUMED_INCLUDE_DIR})

# Find Python
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED) # TODO different version is found
include_directories(${PYTHON_INCLUDE_DIR})

# Find NumPy
find_package(NumPy REQUIRED)
include_directories(${NUMPY_INCLUDE_DIR})

# Find MPI
find_package(MPI)
# TODO optional MPI
include_directories(${MPI_CXX_INCLUDE_PATH})
add_definitions(-D__PLUMED_HAS_MPI) # TODO check PLUMED

# Find MPI4Py
find_package(MPI4Py)
# TODO optional MPI4Py
include_directories(${MPI4PY_INCLUDE_DIR})

# Build PyBias library
add_library(pybias MODULE pybias pybias_plumed)
target_link_libraries(pybias ${PYTHON_LIBRARY})

# Install PyBias library
include(GNUInstallDirs)
install(TARGETS pybias LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
