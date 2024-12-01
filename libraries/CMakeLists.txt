if(NOT TARGET LIB_HW_LIBS)

add_library(LIB_HW_LIBS STATIC "")

add_subdirectory("SPI")
add_subdirectory("Wire")
add_subdirectory("EEPROM")
add_subdirectory("SD")
add_subdirectory("Ethernet")
add_subdirectory("SoftwareSerial")

target_link_libraries(LIB_HW_LIBS
    LIB_SPI
    LIB_WIRE
    LIB_EEPROM
    LIB_SD
    LIB_ETHERNET
    LIB_SOFTWARESERIAL

)

target_include_directories(LIB_HW_LIBS
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/SPI"
        "${CMAKE_CURRENT_LIST_DIR}/Wire"
        "${CMAKE_CURRENT_LIST_DIR}/EEPROM"
        "${CMAKE_CURRENT_LIST_DIR}/SD"
        "${CMAKE_CURRENT_LIST_DIR}/ETHERNET"
        "${CMAKE_CURRENT_LIST_DIR}/SoftwareSerial"
        "${MCU_VARIANT_PATH}"
)

endif()