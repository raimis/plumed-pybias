# Copyright (c) 2017 Raimondas Galvelis

find_program(PLUMED_EXECUTABLE plumed)

execute_process(COMMAND bash -c "${PLUMED_EXECUTABLE} info --configuration | grep ^prefix="
                COMMAND colrm 1 7
                OUTPUT_VARIABLE PLUMED_PREFIX
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# TODO custom "includedir" setting
if(PLUMED_PREFIX)
  set(PLUMED_INCLUDE_DIR ${PLUMED_PREFIX}/inlcude)
endif(PLUMED_PREFIX)

execute_process(COMMAND ${PLUMED_EXECUTABLE} info --long-version
                OUTPUT_VARIABLE PLUMED_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PLUMED
                                  REQUIRED_VARS
                                    PLUMED_EXECUTABLE
                                    PLUMED_PREFIX
                                    PLUMED_INCLUDE_DIR
                                  VERSION_VAR PLUMED_VERSION)
