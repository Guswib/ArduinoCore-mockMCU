if(NOT TARGET LIB_ARDUINO_CORE)
    message("LIB_ARDUINO_CORE target must be created first.")
endif()


if(NOT TARGET LIB_SPI)
add_library(LIB_SPI STATIC "")

target_sources(LIB_SPI
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/SPI.cpp
         
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/SPI.h
)

target_include_directories(LIB_SPI
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(LIB_SPI 
        LIB_ARDUINO_CORE
        )
endif()