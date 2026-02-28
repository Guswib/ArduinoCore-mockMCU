# Check if a variable named 'MY_VARIABLE' is set
if(DEFINED PATH_TO_ARDUINO_API)
   # message("       ArduinoCore: PATH_TO_ARDUINO_API is set. Value: ${PATH_TO_ARDUINO_API}")
else()
    set(PATH_TO_ARDUINO_API "${CMAKE_CURRENT_LIST_DIR}/api")
    message("       ArduinoCore: PATH_TO_ARDUINO_API is not set. Using default." )
endif()


get_directory_property(PARENT_DIR_PATH1 PARENT_DIRECTORY)
get_directory_property(LOCAL_PRJ PARENT_DIRECTORY)


if(NOT DEFINED MCU_VARIANT_PATH)
    set(MCU_VARIANT_PATH "${LOCAL_PRJ}/variants/mock_v1")
    message("       MCU_VARIANT_PATH not set, defaulting to ${MCU_VARIANT_PATH}")
else()
    if(EXISTS "${MCU_VARIANT_PATH}")
        message("       MCU_VARIANT_PATH is set to ${MCU_VARIANT_PATH}")
    else()
        message(FATAL_ERROR "MCU_VARIANT_PATH is set to ${MCU_VARIANT_PATH} but the path does not exist.")
    endif()
endif()

set(header_files
    ${CMAKE_CURRENT_LIST_DIR}/Arduino.h
    ${CMAKE_CURRENT_LIST_DIR}/analog.h

    ${CMAKE_CURRENT_LIST_DIR}/UART.h
    ${CMAKE_CURRENT_LIST_DIR}/Stream.h


    ${CMAKE_CURRENT_LIST_DIR}/mock/MillisFake.h
    ${CMAKE_CURRENT_LIST_DIR}/mock/PrintableMock.h
    ${CMAKE_CURRENT_LIST_DIR}/mock/PrintMock.h
    ${CMAKE_CURRENT_LIST_DIR}/mock/StreamMock.h
) # Creates a list: a;b;c


if(NOT TARGET LIB_ARDUINO_CORE)
    add_library(LIB_ARDUINO_CORE STATIC "")

   


#target_compile_options(LIB_ARDUINO_CORE PRIVATE "-include" "string")
#target_compile_options(LIB_ARDUINO_CORE PRIVATE "-include" "cstring")
     target_sources(LIB_ARDUINO_CORE
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}"         
        FILES ${header_files}
     )

    target_sources(LIB_ARDUINO_CORE
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/digital.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/dtostrf.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/itoa.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART0.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART1.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART2.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART3.cpp 
            ${CMAKE_CURRENT_LIST_DIR}/analog.cpp
    )
    target_include_directories(LIB_ARDUINO_CORE
        PUBLIC 
        #    ${PATH_TO_ARDUINO_API}    #do not include a path to the APU. There will be an issue then string.h .
            ${CMAKE_CURRENT_LIST_DIR}
            ${MCU_VARIANT_PATH}
            ${CMAKE_CURRENT_LIST_DIR}/mock
    )

    add_subdirectory("api" "api" SYSTEM)
    add_subdirectory("${MCU_VARIANT_PATH}" "variant" SYSTEM)

    install(
        TARGETS LIB_ARDUINO_CORE
        RUNTIME_DEPENDENCIES
    )


endif()