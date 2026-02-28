# SPDX-License-Identifier: LGPL-2.1-or-later

#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################

cmake_minimum_required(VERSION 3.25)

##########################################################################

project(example_test LANGUAGES CXX)
cmake_policy(VERSION 3.25)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) # Ensures you use standard C++, not compiler-specific hacks

include (CTest)
#include(FetchContent)
#set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Do not update every time I run cmake, please")

##########################################################################
add_subdirectory(external "external" SYSTEM)


set(LIB_MCU_VARIANT "" )

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRJ_ROOT)
message("\n\n")
message("PROJECT ROOT at:    " ${PRJ_ROOT})
message("Other Paths:")

set(MCU_VARIANT_PATH "${PRJ_ROOT}/variants/mock_v1" )
set(ArduinoCore_SRC_DIR ${PRJ_ROOT}/cores/arduino )


cmake_path(APPEND ArduinoCore_mockMCU_DIR "${PROJECT_SOURCE_DIR}" "build/_deps/HW")
file(COPY "${PROJECT_SOURCE_DIR}/../cores" DESTINATION "${ArduinoCore_mockMCU_DIR}")
#set(arduinoCore ${PROJECT_SOURCE_DIR}/../cores/arduino )
set(arduinoCore ${ArduinoCore_mockMCU_DIR}/cores/arduino )
#file(REMOVE "${ArduinoCore_mockMCU_DIR}/cores/arduino/api")
file(COPY "${ArduinoCore_SRC_DIR}" DESTINATION "${ArduinoCore_mockMCU_DIR}/cores/arduino")


cmake_path(APPEND arduinoCore "${ArduinoCore_mockMCU_DIR}" "cores/arduino")

message("Arduino Core:       ${arduinoCore} - copy")

#include_directories(${arduinoCore}) #Path tho arduino-core
cmake_path(APPEND arduinoCore_API "${ArduinoCore_mockMCU_DIR}" "cores/arduino/api")
message("ArduinpCoreAPI---${arduinoCore_API}")

if(IS_SYMLINK ${arduinoCore_API})
  message("---path to API is a symlink")
endif()


#set(arduinoCore_API ${PROJECT_SOURCE_DIR}/../cores/arduino/api )

cmake_path(APPEND ArduinoCore_API_SRC_DIR "${FETCHCONTENT_BASE_DIR}" "ArduinoCore_API_github-src/api")


if(NOT EXISTS "${ArduinoCore_API_SRC_DIR}/ArduinoAPI.h")
#if(NOT EXISTS "${arduinoCore_API}/ArduinoAPI.h")
  FetchContent_Declare(
    ArduinoCore_API_github
    GIT_REPOSITORY https://github.com/arduino/ArduinoCore-API.git
    GIT_TAG        master
    #SOURCE_DIR  "${ArduinoCore_mockMCU_DIR}/cores/arduino"
  )
  message("Arduino_API: Fetching from github")
  FetchContent_MakeAvailable(ArduinoCore_API_github)

endif()

if(EXISTS "${ArduinoCore_API_SRC_DIR}/ArduinoAPI.h")
    message("---ArduinoCoreAPI found locally")
    file(REMOVE "${ArduinoCore_mockMCU_DIR}/cores/arduino/api")
    file(COPY "${ArduinoCore_API_SRC_DIR}" DESTINATION "${ArduinoCore_mockMCU_DIR}/cores/arduino")

    message("---ArduinoCoreAPI copied")
    set(arduinoCore_API "${ArduinoCore_mockMCU_DIR}/cores/arduino/api")

endif()

set(arduinoCore_API_exists false )
if(EXISTS ${arduinoCore_API})
  set(arduinoCore_API_exists true )
endif()

#set(PATH_TO_ARDUINO_API ${ArduinoCore_API_SRC_DIR})

message("Arduino_API at:      " ${arduinoCore_API} "       exists?" ${arduinoCore_API_exists})


include_directories(external/catch/v2.13.9/include)
#target_include_directories(Catch INTERFACE "external/catch/v2.13.9/include")


message("Included dir:  " ${INCLUDE_DIRECTORIES})

##########################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##########################################################################

set(TEST_TARGET ${CMAKE_PROJECT_NAME})

##########################################################################
message("Included subdir:  " ${arduinoCore})
add_subdirectory("${arduinoCore}" "HW/cores/arduino")

message("Included dir2:  " ${INCLUDE_DIRECTORIES})
add_subdirectory("${PRJ_ROOT}/libraries" "HW/libraries")

#get_target_property(LIB_HW_LIBS_INCLUDES LIB_HW_LIBS INCLUDE_DIRECTORIES)
get_target_property(LIB_ARDUINO_CORE_INCLUDES LIB_ARDUINO_CORE INCLUDE_DIRECTORIES)
##SELECT WHICH VARIANT TO USE:
#get_target_property(LIB_VARIANT_INCLUDES LIB_VARIANT_MOCK_V1 INCLUDE_DIRECTORIES)



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
add_subdirectory(src) #adds all tests


get_target_property(LIB_HARDWARE_INCLUDES ${TEST_TARGET} SOURCES)
    message("SOURCES")
    foreach(dir ${LIB_HARDWARE_INCLUDES})
        message(STATUS "  - ${dir}")
    endforeach()

get_target_property(LIB_HARDWARE_INCLUDES ${TEST_TARGET} INCLUDE_DIRECTORIES)
    message("LIB_HARDWARE_INCLUDES")
    foreach(dir ${LIB_HARDWARE_INCLUDES})
        message(STATUS "  - ${dir}")
    endforeach()
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
  PUBLIC LIB_ARDUINO_CORE
  PUBLIC LIB_HW_LIBS

  #PUBLIC LIB_VARIANT_MOCK_V1
)
#include_directories(${PRJ_ROOT}/variants/mock_v1)
target_compile_options(${TEST_TARGET} PRIVATE "-include" "cstring")

# find_package(Catch REQUIRED)
enable_testing()
include(Catch)
add_test(NAME MockV1testing COMMAND ${TEST_TARGET} )
#include_directories("C:/msys64/mingw64/include")
# add_test(NAME catch_test COMMAND ${TEST_TARGET} --success)

catch_discover_tests(${TEST_TARGET})
