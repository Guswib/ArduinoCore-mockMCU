
#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################
set(TEST_TARGET "UnitTest" )

cmake_minimum_required(VERSION 3.25)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5
)
 
set( CMAKE_C_COMPILER   "C:/msys64/mingw64/bin/gcc.exe" )
set( CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe" )
#set( CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe" )
#set( CMAKE_C_COMPILER   "C:/MinGW/bin/gcc.exe" )
#set( CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe" )
#set( CMAKE_C_COMPILER   "C:/msys64/ucrt64/bin/gcc.exe" )
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
include_directories(./include)
message("Other Paths:")
#cmake_path(APPEND HARDWARE "${PRJ_ROOT}" "hardware/arduino-git")
cmake_path(APPEND SOFTWARE "${PRJ_ROOT}" "extras")

#message("Hardware Paths:" ${HARDWARE})

add_subdirectory(external)


message("\n\nFetchContent_MakeAvailable####################################################################")
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

cmake_path(APPEND googletest_DIR "${FETCHCONTENT_BASE_DIR}" "googletest-src")

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(ArduinoCore_mockMCU)

cmake_path(APPEND ArduinoBufferedStreams_DIR "${FETCHCONTENT_BASE_DIR}" "ArduinoBufferedStreams-src")

include(GNUInstallDirs)

enable_testing()
include(GoogleTest)

add_subdirectory("src" "src_build")




target_link_libraries(
    ${TEST_TARGET} 
   # PUBLIC LIB_HARDWARE
  PUBLIC LIB_ARDUINO_CORE
  PUBLIC LIB_HW_LIBS
    PUBLIC gtest 
    PUBLIC gtest_main
  #  PUBLIC "${ArduinoCore_mockMCU_DIR}/cores/arduino/api/deprecated"
#virtual_instrument
)


gtest_discover_tests(${TEST_TARGET})

add_test(NAME ${TEST_TARGET}
         COMMAND ${TEST_TARGET}
         )
