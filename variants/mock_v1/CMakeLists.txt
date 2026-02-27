message("Variant:")

#if(NOT TARGET LIB_VARIANT_MOCK_V1)
if(TARGET LIB_ARDUINO_CORE)
    message("   Variant:MOCK V1 added to core.")

   # add_library(LIB_VARIANT_MOCK_V1 STATIC "")

    target_sources(LIB_ARDUINO_CORE
        PUBLIC
            
            "${CMAKE_CURRENT_LIST_DIR}/variant.cpp" 

            "${CMAKE_CURRENT_LIST_DIR}/PrintMock.cpp"  
            "${CMAKE_CURRENT_LIST_DIR}/StreamMock.cpp"  
            "${CMAKE_CURRENT_LIST_DIR}/MillisFake.cpp"  
        
            
        PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/pins_arduino.h"  
            "${CMAKE_CURRENT_LIST_DIR}/avr/pgmspace.h"        

    )

 #   target_include_directories(LIB_VARIANT_MOCK_V1
 #       PUBLIC
 #           "${CMAKE_CURRENT_LIST_DIR}"
 #          # "${PATH_TO_ARDUINO_API}"
 #   )
    message("\nAdding Variant Mock V1  ---   " ${CMAKE_CURRENT_LIST_DIR})
    set(MCU_VARIANT_PATH ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
    set(LIB_MCU_VARIANT ${LIB_VARIANT_MOCK_V1} PARENT_SCOPE)
    
 #   target_link_libraries(LIB_VARIANT_MOCK_V1
 #       PUBLIC LIB_ARDUINO_CORE_API
 #   )
 #   install(
 #       TARGETS LIB_VARIANT_MOCK_V1
 #       RUNTIME_DEPENDENCIES
 #   )

endif()