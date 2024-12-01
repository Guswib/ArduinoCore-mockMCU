if(NOT TARGET LIB_EEPROM)
    add_library(LIB_EEPROM STATIC "")

    target_sources(LIB_EEPROM
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/EEPROM.cpp        
            
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/EEPROM.h
    )
    target_include_directories(LIB_EEPROM
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
    )
endif()