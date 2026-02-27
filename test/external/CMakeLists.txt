
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
  virtual_instrument
  GIT_REPOSITORY https://github.com/Guswib/Virtual_Instrument.git
  GIT_TAG        main
)

FetchContent_Declare(
  ArduinoBufferedStreams
  GIT_REPOSITORY https://github.com/paulo-raca/ArduinoBufferedStreams.git
  GIT_TAG        master
)

FetchContent_Declare(
  ArduinoCore_mockMCU
  GIT_REPOSITORY https://github.com/Guswib/ArduinoCore-mockMCU.git
  GIT_TAG        main
)

FetchContent_Declare(
  ArduinoCore_API
  GIT_REPOSITORY https://github.com/arduino/ArduinoCore-API.git
  GIT_TAG        master
  #SOURCE_DIR  "${ArduinoCore_mockMCU_DIR}/cores/arduino"
)

FetchContent_Declare(
  Virtual_Potentiostat
  GIT_REPOSITORY https://github.com/Guswib/Virtual_Potentiostat.git
  GIT_TAG        main
  #SOURCE_DIR  "${ArduinoCore_mockMCU_DIR}/cores/arduino"
)

message("\n\nFetchContent_MakeAvailable####################################################################")
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


#if(NOT EXISTS "${googletest_DIR}")
message("Fetch GoogleTest")
FetchContent_MakeAvailable(googletest)

message("Fetch ArduinoCore_mockMCU")
FetchContent_MakeAvailable( ArduinoCore_mockMCU)
