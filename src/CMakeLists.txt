
# Find PLUMED
# TODO find PLUMED
include_directories(~/opt/plumed/2.2.2/include)
include_directories(~/opt/plumed/include) # Travis

# Find Python
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})
get_filename_component(PYTHON_LIBRARY_NAME ${PYTHON_LIBRARY} NAME)
add_definitions(-DLDLIBRARY="${PYTHON_LIBRARY_NAME}")

# Find NumPy
#find_package(NumPy REQUIRED)

# Find MPI
find_package(MPI)
# TODO optional MPI
include_directories(${MPI_CXX_INCLUDE_PATH})
add_definitions(-D__PLUMED_HAS_MPI)

# Find MPI4Py
# TODO optional MPI4Py
#find_package(MPI4PY)
#include_directories(${MPI4PY_INCLUDE_DIR})
include_directories(/usr/lib64/python2.7/site-packages/openmpi/mpi4py/include)
include_directories(/usr/lib/python2.7/dist-packages/mpi4py/include) # Travis

add_library(pybias MODULE pybias.cpp)
# TODO remove direct linking to Python library
target_link_libraries(pybias python2.7)

