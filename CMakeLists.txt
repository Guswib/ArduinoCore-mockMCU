
# ./source3/CMakeLists.txt

# CMakeLists.txt for the hardware layer of the project


set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

message("Adding Hardware #######################################################")
cmake_path(APPEND arduinoHW "${dir}")
cmake_path(APPEND arduinoHW_Core "${arduinoHW}" "cores/arduino")
cmake_path(APPEND arduinoHW_CoreAPI "${arduinoHW_Core}" "api")
cmake_path(APPEND arduinoHW_Lib "${arduinoHW}" "libraries")
cmake_path(APPEND arduinoHW_Variants "${arduinoHW}" "variants")
message(${arduinoHW_Core})

set(MCU_VARIANT_PATH "${arduinoHW_Variants}/mock_v1" )
set(LIB_MCU_VARIANT "" )


#include_directories(${arduinoCore}) #Path tho arduino-core
#include_directories(${arduinoCoreAPI}) #Path tho arduino-core

#include_directories(${arduinoCoreLib}/Wire) #Path tho arduino-core
#include_directories(${arduinoCoreLib}/SPI) #Path tho arduino-core
#include_directories(${arduinoCoreVariants}/mock_v1) #Path tho arduino-core


#add_subdirectory(${arduinoCoreLib}/SPI)
#add_subdirectory(${arduinoCoreLib}/Wire)

if(NOT TARGET LIB_HARDWARE)
    add_library(LIB_HARDWARE STATIC "")
    
    add_subdirectory(${arduinoHW_Core} "HW/cores")
    add_subdirectory(${arduinoHW_Variants}/mock_v1 "HW/variants/mock_v1")
    # add_subdirectory(${arduinoCore})
    add_subdirectory(${arduinoHW_Lib} "HW/libraries")

    get_target_property(LIB_HW_LIBS_INCLUDES LIB_HW_LIBS INCLUDE_DIRECTORIES)
    get_target_property(LIB_ARDUINO_CORE_INCLUDES LIB_ARDUINO_CORE INCLUDE_DIRECTORIES)
    get_target_property(LIB_VARIANT_MOCK_V1_INCLUDES LIB_VARIANT_MOCK_V1 INCLUDE_DIRECTORIES)

    target_include_directories(LIB_HARDWARE 
        PUBLIC ${LIB_ARDUINO_CORE_INCLUDES}    
        PUBLIC ${LIB_VARIANT_MOCK_V1_INCLUDES}
        PUBLIC ${LIB_HW_LIBS_INCLUDES}
    )

    include_directories( 
     ${LIB_ARDUINO_CORE_INCLUDES}    
     ${LIB_VARIANT_MOCK_V1_INCLUDES}
     ${LIB_HW_LIBS_INCLUDES}
    )

    target_link_libraries(LIB_HARDWARE 
        #LIB_SPI
        #LIB_WIRE
        PUBLIC LIB_ARDUINO_CORE
        PUBLIC LIB_VARIANT_MOCK_V1
        PUBLIC LIB_HW_LIBS
        
        
    )
    message("\nADDING THE HARDWARE######:  ")
    get_target_property(LIB_HARDWARE_INCLUDES LIB_HARDWARE INCLUDE_DIRECTORIES)
    message(${LIB_HARDWARE_INCLUDES})
    foreach(dir ${LIB_HARDWARE_INCLUDES})
    message(STATUS "  - ${dir}")
endforeach()

    message("")

endif()

message("\nADD HARDWARE###### ENDED##########33\n")