
# CMakeLists.txt for the hardware layer of the project
include(FetchContent)


#set(BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
message("Adding Hardware #######################################################")

#################################################
#Download ArduinoCore_API

set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Do not update every time I run cmake, please")
FetchContent_Declare(
    ArduinoCore_API_github
    GIT_REPOSITORY https://github.com/arduino/ArduinoCore-API.git
    GIT_TAG        master
    #SOURCE_DIR  "${ArduinoCore_mockMCU_DIR}/cores/arduino"
  )
FetchContent_MakeAvailable(ArduinoCore_API_github)

cmake_path(APPEND ARDUINO_HW "${FETCHCONTENT_BASE_DIR}" "HW_temp")

cmake_path(APPEND ArduinoCore_API_SRC_DIR "${FETCHCONTENT_BASE_DIR}" "ArduinoCore_API_github-src/api")
file(COPY "${ArduinoCore_API_SRC_DIR}" DESTINATION "${ARDUINO_HW}/cores/arduino")

cmake_path(APPEND arduinoHW_Core "${BASE_DIR}" "cores")
message("Copy ${arduinoHW_Core}")
file(COPY "${arduinoHW_Core}" DESTINATION "${ARDUINO_HW}")

add_subdirectory(${ARDUINO_HW}/cores/arduino "HW/cores/arduino" SYSTEM)

#cmake_path(APPEND arduinoHW_CoreAPI "${arduinoHW_Core}" "api")
cmake_path(APPEND arduinoHW_Lib "${BASE_DIR}" "libraries")
add_subdirectory(${arduinoHW_Lib} "HW/libraries")

message(${arduinoHW_Core})

#set(MCU_VARIANT_PATH "${arduinoHW_Variants}/mock_v1" )

#####################


if(NOT TARGET LIB_HARDWARE)
    add_library(LIB_HARDWARE STATIC "")
    
   target_link_libraries(LIB_HARDWARE 
        PUBLIC LIB_ARDUINO_CORE
        PUBLIC LIB_HW_LIBS

        
    )
    message("\nADDING THE HARDWARE######:  ")
   # get_target_property(LIB_HARDWARE_INCLUDES LIB_HARDWARE INCLUDE_DIRECTORIES)
    list(REMOVE_DUPLICATES LIB_HARDWARE_INCLUDES)
    set_target_properties(LIB_HARDWARE PROPERTIES INCLUDE_DIRECTORIES "${LIB_HARDWARE_INCLUDES}")
    
   # get_target_property(LIB_HARDWARE_INCLUDES LIB_HARDWARE INCLUDE_DIRECTORIES)
   # message("LIB_HARDWARE_INCLUDES")
   # foreach(dir ${LIB_HARDWARE_INCLUDES})
   #     message(STATUS "  - ${dir}")
   # endforeach()

    message("")

endif()

message("\nADD HARDWARE###### ENDED##########33\n")