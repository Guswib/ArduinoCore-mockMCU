
#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################
set(TEST_TARGET "UnitTest" )

cmake_minimum_required(VERSION 3.25)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5
)
 
#set( CMAKE_C_COMPILER   "C:/msys64/mingw64/bin/gcc.exe" )
#set( CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe" )

##########################################################################
set(This test_unit )


project(${This} C CXX)

add_executable(
  "${TEST_TARGET}" ""
)

# project(ECiLoggerTest LANGUAGES CXX)
include (CTest)
#project(example_test LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)




cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRJ_ROOT)
set(PRJ_ROOT "${PROJECT_SOURCE_DIR}")
message("\n\n")
message("PROJECT ROOT at:    " ${PRJ_ROOT})

message("Other Paths:")
#cmake_path(APPEND HARDWARE "${PRJ_ROOT}" "hardware/arduino-git")
cmake_path(APPEND SOFTWARE "${PRJ_ROOT}" "extras")

#message("Hardware Paths:" ${HARDWARE})

set(MCU_VARIANT_PATH "${PRJ_ROOT}/../variants/mock_v1" )

message("\n\nFetchContent_MakeAvailable####################################################################")
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(GET_ARDUINO_API ON)
add_subdirectory(external)

cmake_path(APPEND arduinoHW_Core "${PRJ_ROOT}/.." "cores")
message("Copy ${arduinoHW_Core}")
cmake_path(APPEND ARDUINO_HW "${FETCHCONTENT_BASE_DIR}" "HW_temp")
file(COPY "${arduinoHW_Core}" DESTINATION "${ARDUINO_HW}")

add_subdirectory("${ARDUINO_HW}/cores/arduino" )
add_subdirectory("../libraries" "HW/libraries" SYSTEM)


include(GNUInstallDirs)

enable_testing()
include(GoogleTest)


add_subdirectory("src" "src_build")

target_link_libraries(
  ${TEST_TARGET} 

  PUBLIC LIB_ARDUINO_CORE
  PUBLIC LIB_HW_LIBS
  PUBLIC gtest 
  PUBLIC gtest_main
 
)


gtest_discover_tests(${TEST_TARGET})

add_test(NAME ${TEST_TARGET}
         COMMAND ${TEST_TARGET}
         )
