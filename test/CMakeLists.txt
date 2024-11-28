# SPDX-License-Identifier: LGPL-2.1-or-later

#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################

cmake_minimum_required(VERSION 3.25)

##########################################################################

project(example_test)
include (CTest)
##########################################################################

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRJ_ROOT)

message("\n\nPROJECT ROOT at: " ${PRJ_ROOT})
include_directories(./include)
message("Other Paths:")

set(arduinoCore ${PROJECT_SOURCE_DIR}/../cores/arduino )
cmake_path(APPEND arduinoCore "${PRJ_ROOT}" "cores/arduino")

message("Arduino Core:   "${arduinoCore})

include_directories(${arduinoCore}) #Path tho arduino-core
cmake_path(APPEND arduinoCore_API "${PRJ_ROOT}" "cores/arduino/api")

#set(arduinoCore_API ${PROJECT_SOURCE_DIR}/../cores/arduino/api )

if(NOT EXISTS "${arduinoCore_API}/arduino-api.h")
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




include_directories(../variants/mock_v1) #Path tho arduino-core

include_directories(external/catch/v2.13.9/include)

message("Included dir:  " ${INCLUDE_DIRECTORIES})
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

# set(arduinoCore-API )
set(TEST_DUT_SRCS
   
  .
  ${arduinoCore_API}/Stream.cpp
  ${arduinoCore_API}/String.cpp
  ${arduinoCore_API}/Print.cpp
  ${arduinoCore_API}/Common.cpp

  ${arduinoCore}/UART.cpp
  ${arduinoCore}/UART0.cpp
  ${arduinoCore}/UART1.cpp
  ${arduinoCore}/UART2.cpp
  ${arduinoCore}/UART3.cpp
  ../variants/mock_v1/variant.cpp
)
#message(${TEST_DUT_SRCS})
##########################################################################

set(TEST_TARGET_SRCS
  src/main.cpp
  #src/dtostrf.cpp
  ${arduinoCore}/dtostrf.cpp
  #src/itoa.cpp
  ${arduinoCore}/itoa.cpp
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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

##########################################################################

add_executable(
  ${TEST_TARGET}
  ${TEST_TARGET_SRCS}
)

##########################################################################