if(NOT TARGET LIB_MCU_VARIANT_MOCK_V1)
   
    add_library(LIB_VARIANT_MOCK_V1 STATIC "")

    target_sources(LIB_VARIANT_MOCK_V1
        PUBLIC
            
            "${CMAKE_CURRENT_LIST_DIR}/variant.cpp"  
        
            
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/pins_arduino.h"        

    )

    target_include_directories(LIB_VARIANT_MOCK_V1
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}"
            ${CMAKE_CURRENT_LIST_DIR}/../../cores/Arduino
    )
    message("\nAdding Variant Mock V1  ---   " ${CMAKE_CURRENT_LIST_DIR})
    set(MCU_VARIANT_PATH ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
    set(LIB_MCU_VARIANT ${LIB_VARIANT_MOCK_V1} PARENT_SCOPE)
    install(
        TARGETS LIB_VARIANT_MOCK_V1
        RUNTIME_DEPENDENCIES
    )

endif()