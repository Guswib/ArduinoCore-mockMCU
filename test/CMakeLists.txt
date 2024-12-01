# SPDX-License-Identifier: LGPL-2.1-or-later

#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################

cmake_minimum_required(VERSION 3.25)

##########################################################################

project(example_test LANGUAGES CXX)
include (CTest)
##########################################################################

set(MCU_VARIANT_PATH "" )
set(LIB_MCU_VARIANT "" )

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRJ_ROOT)
message("\n\n")
message("PROJECT ROOT at:    " ${PRJ_ROOT})
include_directories(./include)
message("Other Paths:")

set(arduinoCore ${PROJECT_SOURCE_DIR}/../cores/arduino )
cmake_path(APPEND arduinoCore "${PRJ_ROOT}" "cores/arduino")

message("Arduino Core:       ${arduinoCore}")

include_directories(${arduinoCore}) #Path tho arduino-core
cmake_path(APPEND arduinoCore_API "${PRJ_ROOT}" "cores/arduino/api")
if(IS_SYMLINK ${arduinoCore_API})
  message("---path to API is a symlink")
endif()

#set(arduinoCore_API ${PROJECT_SOURCE_DIR}/../cores/arduino/api )

if(NOT EXISTS "${arduinoCore_API}/ArduinoAPI.h")
  cmake_path(GET PRJ_ROOT PARENT_PATH arduinoCore_API)
  cmake_path(APPEND arduinoCore_API "${arduinoCore_API}" "ArduinoCore-API/api")

  #set(arduinoCore_API ${PROJECT_SOURCE_DIR}/../ArduinoCore-API/api )
  #include_directories(../ArduinoCore-API/api)
endif()
set(arduinoCore_API_exists false )
if(EXISTS ${arduinoCore_API})
  set(arduinoCore_API_exists true )
endif()
message("Arduino_API at:      " ${arduinoCore_API} "       exists?" ${arduinoCore_API_exists})

cmake_path(APPEND arduinoCoreLib "${PRJ_ROOT}" "libraries")

#include_directories(${arduinoCoreLib}/Wire) #Path tho arduino-core
#include_directories(${arduinoCoreLib}/SPI) #Path tho arduino-core
include_directories(../variants/mock_v1) #Path tho arduino-core

include_directories(external/catch/v2.13.9/include)
#target_include_directories(Catch INTERFACE "external/catch/v2.13.9/include")


message("Included dir:  " ${INCLUDE_DIRECTORIES})
##########################################################################

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##########################################################################

set(TEST_TARGET ${CMAKE_PROJECT_NAME})

##########################################################################
add_subdirectory("${PRJ_ROOT}/variants/mock_v1" "HW/variants/mock_v1")
add_subdirectory("${PRJ_ROOT}/cores/arduino" "HW/core/arduino")
add_subdirectory("${PRJ_ROOT}/libraries" "HW/libraries")

get_target_property(LIB_HW_LIBS_INCLUDES LIB_HW_LIBS INCLUDE_DIRECTORIES)
get_target_property(LIB_ARDUINO_CORE_INCLUDES LIB_ARDUINO_CORE INCLUDE_DIRECTORIES)
##SELECT WHICH VARIANT TO USE:
get_target_property(LIB_VARIANT_INCLUDES LIB_VARIANT_MOCK_V1 INCLUDE_DIRECTORIES)


##########################################################################

set(TEST_SRCS
 
  src/Stream/test_find.cpp
  src/Stream/test_findUntil.cpp
  src/Stream/test_getTimeout.cpp
  src/Stream/test_parseFloat.cpp
  src/Stream/test_parseInt.cpp
  src/Stream/test_readBytes.cpp
  src/Stream/test_readBytesUntil.cpp
  src/Stream/test_readString.cpp
  src/Stream/test_readStringUntil.cpp
  src/Stream/test_setTimeout.cpp
 
  src/Serial/test_Serial.cpp
  src/SPI/test_SPI.cpp
  
   
)

# set(arduinoCore-API )
set(TEST_DUT_SRCS
   
  .
  #${arduinoCore_API}/Stream.cpp
  #${arduinoCore_API}/String.cpp
  #${arduinoCore_API}/Print.cpp
  #${arduinoCore_API}/Common.cpp

 
  #${arduinoCore}/UART.cpp
  #${arduinoCore}/UART0.cpp
  #${arduinoCore}/UART1.cpp
  #${arduinoCore}/UART2.cpp
  #${arduinoCore}/UART3.cpp

  #${arduinoCoreLib}/SPI/SPI.cpp
  #${arduinoCoreLib}/Wire/Wire.cpp

  #../variants/mock_v1/variant.cpp
)
#message(${TEST_DUT_SRCS})
##########################################################################

set(TEST_TARGET_SRCS
  src/main.cpp
  #src/dtostrf.cpp
  #${arduinoCore}/dtostrf.cpp
  #src/itoa.cpp
  #${arduinoCore}/itoa.cpp
  src/MillisFake.cpp
  src/PrintMock.cpp
  src/StreamMock.cpp
  ${TEST_SRCS}
  ${TEST_DUT_SRCS}
)
##########################################################################

add_compile_definitions(HOST)
#add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_compile_options(-Wno-cast-function-type) 
#add_compile_options(-Werror=unused-parameter)
add_compile_options(-ftest-coverage) 

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} --coverage")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -Wno-deprecated-copy -fprofile-arcs")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs")
#set( CMAKE_EXE_LINKER_FLAGS "$CMALE_EXE_LINKER_FLAGS")

##########################################################################

include(FetchContent)

FetchContent_Declare(
  Catch2 
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.10
  )
  
cmake_path(APPEND catch2_SOURCE_DIR "${PROJECT_SOURCE_DIR}" "build/_deps/catch2-src")

list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
FetchContent_MakeAvailable(Catch2)



#######################################

add_executable(
  ${TEST_TARGET}
  ${TEST_TARGET_SRCS}
)
#######################################################################
target_include_directories(
  ${TEST_TARGET} 
  PUBLIC ${LIB_HW_LIBS_INCLUDES}
  PUBLIC ${LIB_ARDUINO_CORE_INCLUDES}
  PUBLIC ${LIB_VARIANT_INCLUDES}
  PUBLIC ${MCU_VARIANT_PATH}
)


#target_include_directories(${TEST_TARGET} PUBLIC )
#target_include_directories(${TEST_TARGET} PUBLIC )
#include_directories(
#  ${LIB_HW_LIBS_INCLUDES}
#${LIB_ARDUINO_CORE_INCLUDES}
#${LIB_VARIANT_INCLUDES})
#set(ALL_INCLUDED )
#get_target_property(ALL_INCLUDES ${TEST_TARGET} INCLUDE_DIRECTORIES)
#message("INCLUIDE\n" ${LIB_ARDUINO_CORE_INCLUDES} )
##########################################################################
#target_link_libraries(${TEST_TARGET} PUBLIC Catch2::Catch2)
target_link_libraries(${TEST_TARGET} 
  PUBLIC Catch2::Catch2
  PUBLIC LIB_HW_LIBS
  PUBLIC LIB_ARDUINO_CORE
  PUBLIC LIB_VARIANT_MOCK_V1
)
#include_directories(${PRJ_ROOT}/variants/mock_v1)

# find_package(Catch REQUIRED)
enable_testing()
include(Catch)
add_test(NAME MockV1testing COMMAND ${TEST_TARGET} )
# add_test(NAME catch_test COMMAND ${TEST_TARGET} --success)

catch_discover_tests(${TEST_TARGET})
