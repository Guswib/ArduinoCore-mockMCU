if(NOT TARGET LIB_WIRE)

    add_library(LIB_WIRE STATIC "")

    target_sources(LIB_WIRE
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/Wire.cpp
            
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/Wire.h
    )
    target_include_directories(LIB_WIRE
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
            ${MCU_VARIANT_PATH}
    )
    target_link_libraries(LIB_WIRE 
        LIB_ARDUINO_CORE
        )
endif()