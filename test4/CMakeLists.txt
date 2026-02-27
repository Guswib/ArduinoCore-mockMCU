# SPDX-License-Identifier: LGPL-2.1-or-later

#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################

cmake_minimum_required(VERSION 3.25)

##########################################################################

project(example_test4 LANGUAGES CXX)

set(TEST_TARGET ${CMAKE_PROJECT_NAME})


include(CTest)
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Do not update every time I run cmake, please")

include(FetchContent)

FetchContent_Declare(
  Catch2 
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.10
  )
  message("Fetching Catch2 from github")

FetchContent_MakeAvailable(Catch2)


cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRJ_ROOT)
message("PROJECT ROOT at:    " ${PRJ_ROOT})

##########################################################################

set(MCU_VARIANT_PATH "" )
set(LIB_MCU_VARIANT "" )


set(dir "${CMAKE_CURRENT_SOURCE_DIR}")
message("Adding Hardware #######################################################")
cmake_path(APPEND arduinoHW "${dir}/..")
cmake_path(APPEND arduinoHW_Core "${PRJ_ROOT}")
cmake_path(APPEND arduinoHW_Variants "${arduinoHW}" "variants")
message(${arduinoHW_Core})

set(MCU_VARIANT_PATH "${arduinoHW_Variants}/mock_v1" )
set(LIB_MCU_VARIANT "" )

message("\nADDING THE HARDWARE######: ${arduinoHW_Core} ")

add_subdirectory(${PRJ_ROOT} "HW2")

message("\nADDING THE HARDWARE######:  ")

foreach(dir ${LIB_HARDWARE_INCLUDES})
    message(STATUS "  - ${dir}")
endforeach()
add_executable(
  ${TEST_TARGET}
 "src/main.cpp"
)

target_include_directories(
  ${TEST_TARGET} 
  PUBLIC "${FETCHCONTENT_BASE_DIR}/Catch2-src/include"
)

target_link_libraries(${TEST_TARGET} 
  #PUBLIC Catch2::Catch2
  PUBLIC Catch2
  PUBLIC LIB_HARDWARE
#  PUBLIC LIB_ARDUINO_CORE
  #PUBLIC LIB_VARIANT_MOCK_V1
)


#include(Catch2)