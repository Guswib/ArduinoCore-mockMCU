# SPDX-License-Identifier: LGPL-2.1-or-later

#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################

cmake_minimum_required(VERSION 3.31)
#cmake_policy(VERSION 4.2)

##########################################################################

project(test_as_external_lib LANGUAGES CXX)

set(TEST_TARGET UnitTest)


include(CTest)
include(GNUInstallDirs)
include(GoogleTest)
enable_testing()

#message("PROJECT ROOT at:    " ${CMAKE_CURRENT_SOURCE_DIR})

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PRJ_ROOT1)
cmake_path(GET PRJ_ROOT1 PARENT_PATH PRJ_ROOT)

message("PROJECT ROOT at:    " ${PRJ_ROOT})

##########################################################################
add_executable(
  ${TEST_TARGET}
 ""
)

add_subdirectory("../external" "external")

add_subdirectory(${PRJ_ROOT} "HW2")


add_subdirectory("../src" "src_build")


target_link_libraries(
  ${TEST_TARGET} 
  PUBLIC gtest 
  PUBLIC gtest_main
  PUBLIC LIB_HARDWARE

)


gtest_discover_tests(${TEST_TARGET})

add_test(NAME ${TEST_TARGET}
         COMMAND ${TEST_TARGET}
         )

add_compile_definitions( HOST 1)
