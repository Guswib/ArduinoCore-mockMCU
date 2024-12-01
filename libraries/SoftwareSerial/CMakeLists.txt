if(NOT TARGET LIB_SOFTWARESERIAL)

    add_library(LIB_SOFTWARESERIAL STATIC "")

    target_sources(LIB_SOFTWARESERIAL
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/SoftwareSerial.cpp
           
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/SoftwareSerial.h
   
    )
    target_include_directories(LIB_SOFTWARESERIAL
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
            ${MCU_VARIANT_PATH}
    )
    target_link_libraries(LIB_SOFTWARESERIAL 
        LIB_ARDUINO_CORE
        )
endif()