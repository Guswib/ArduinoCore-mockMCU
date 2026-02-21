
# ./source3/CMakeLists.txt

# CMakeLists.txt for the hardware layer of the project


set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

message("Adding Hardware #######################################################")
cmake_path(APPEND arduinoHW "${dir}")
cmake_path(APPEND arduinoCore "${arduinoHW}" "cores/arduino")
cmake_path(APPEND arduinoCoreAPI "${arduinoCore}" "api")
cmake_path(APPEND arduinoCoreLib "${arduinoHW}" "libraries")
cmake_path(APPEND arduinoCoreVariants "${arduinoHW}" "variants")
message(${arduinoCore})

set(MCU_VARIANT_PATH "${arduinoCoreVariants}/mock_v1" )
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
    
    add_subdirectory(${arduinoCore})
    add_subdirectory(${arduinoCoreVariants}/mock_v1)
    # add_subdirectory(${arduinoCore})
    add_subdirectory(${arduinoCoreLib})

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
    message("")

endif()
message("\nADD HARDWARE###### ENDED##########33\n")