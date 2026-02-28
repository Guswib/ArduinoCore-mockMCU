
#Set up everuthing:
# cmake -G "MinGW Makefiles"
##########################################################################
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)




set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Do not update every time I run cmake, please")

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)


FetchContent_Declare(
  ArduinoBufferedStreams
  GIT_REPOSITORY https://github.com/paulo-raca/ArduinoBufferedStreams.git
  GIT_TAG        master
)



FetchContent_Declare(
  ArduinoCore_API_github
  GIT_REPOSITORY https://github.com/arduino/ArduinoCore-API.git
  GIT_TAG        master
  #SOURCE_DIR  "${ArduinoCore_mockMCU_DIR}/cores/arduino"
)



message("\n\nFetchContent_MakeAvailable####################################################################")
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


#if(NOT EXISTS "${googletest_DIR}")
message("Fetch GoogleTest")
FetchContent_MakeAvailable(googletest)

if(DEFINED GET_ARDUINO_API)
  message("Fetch ArduinoCore_API")
  FetchContent_MakeAvailable( ArduinoCore_API_github)
  cmake_path(APPEND ARDUINO_HW "${FETCHCONTENT_BASE_DIR}" "HW_temp")
  cmake_path(APPEND ArduinoCore_API_SRC_DIR "${FETCHCONTENT_BASE_DIR}" "ArduinoCore_API_github-src/api")
  file(COPY "${ArduinoCore_API_SRC_DIR}" DESTINATION "${ARDUINO_HW}/cores/arduino")
  
endif()
