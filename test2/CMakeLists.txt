# SPDX-License-Identifier: LGPL-2.1-or-later

#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################

cmake_minimum_required(VERSION 3.25)

##########################################################################

project(example_test2 LANGUAGES CXX)
include (CTest)
include(FetchContent)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRJ_ROOT)
message("PROJECT ROOT at:    " ${PRJ_ROOT})

##########################################################################

set(MCU_VARIANT_PATH "" )
set(LIB_MCU_VARIANT "" )


set(dir "${CMAKE_CURRENT_SOURCE_DIR}")
message("Adding Hardware #######################################################")
cmake_path(APPEND arduinoHW "${dir}/..")
cmake_path(APPEND arduinoHW_Core "${PRJ_ROOT}")
message("\nADDING THE HARDWARE######: ${arduinoHW_Core} ")

add_subdirectory(${arduinoHW_Core} "cores/arduino")

message("\nADDING THE HARDWARE######:  ")
get_target_property(LIB_HARDWARE_INCLUDES LIB_ARDUINO_CORE INCLUDE_DIRECTORIES)
foreach(dir ${LIB_ARDUINO_CORE})
    message(STATUS "  - ${dir}")
endforeach()

cmake_path(APPEND arduinoHW_Core "${PRJ_ROOT}")
cmake_path(APPEND arduinoHW_Variants "${arduinoHW}" "variants")
cmake_path(APPEND MCU_VARIANT_PATH "${arduinoHW_Variants}/mock_v1" )
add_subdirectory(${MCU_VARIANT_PATH} "variant/mock_v1")

message("\nADDING THE variant######:  ")
    get_target_property(LIB_HARDWARE_INCLUDES LIB_ARDUINO_CORE INCLUDE_DIRECTORIES)
    message(${LIB_ARDUINO_CORE})
    foreach(dir ${LIB_ARDUINO_CORE})
    message(STATUS "  - ${dir}")
endforeach()



cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRJ_ROOT)
message("\n\n")
message("PROJECT ROOT at:    " ${PRJ_ROOT})

