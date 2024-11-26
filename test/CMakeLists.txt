# SPDX-License-Identifier: LGPL-2.1-or-later

##########################################################################

cmake_minimum_required(VERSION 3.25)

##########################################################################

project(exmaple_test)
include (CTest)
##########################################################################

include_directories(../cores/arduino) #Path tho arduino-core
include_directories(../variants/mock_v1) #Path tho arduino-core

include_directories(include)
include_directories(external/catch/v2.13.9/include)
set(arduinoCore_API ../../ArduinoCore-API )
include_directories(${arduinoCore_API}) #Path tho arduino-core

##########################################################################



set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##########################################################################

set(TEST_TARGET ${CMAKE_PROJECT_NAME})

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
   
)

set(arduinoCore-API )
set(TEST_DUT_SRCS
   
  .
  ${arduinoCore_API}/api/Stream.cpp
  ${arduinoCore_API}/api/String.cpp
  ${arduinoCore_API}/api/Print.cpp
  ${arduinoCore_API}/api/Common.cpp

  ../variants/mock_v1/variant.cpp
)

##########################################################################

set(TEST_TARGET_SRCS
  src/main.cpp
  #src/dtostrf.cpp
  ../cores/arduino/dtostrf.cpp
  #src/itoa.cpp
  ../cores/arduino/itoa.cpp
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

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -Wno-deprecated-copy")

##########################################################################

add_executable(
  ${TEST_TARGET}
  ${TEST_TARGET_SRCS}
)

##########################################################################