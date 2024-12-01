if(NOT TARGET LIB_SD)

    add_library(LIB_SD STATIC "")

    target_sources(LIB_SD
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/SD.cpp
            ${CMAKE_CURRENT_LIST_DIR}/File.cpp
            ${CMAKE_CURRENT_LIST_DIR}/utility/SdFile.cpp
            ${CMAKE_CURRENT_LIST_DIR}/utility/SdVolume.cpp
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/SD.h
            ${CMAKE_CURRENT_LIST_DIR}/utility/FatStructs.h
            ${CMAKE_CURRENT_LIST_DIR}/utility/Sd2Card.h
            ${CMAKE_CURRENT_LIST_DIR}/utility/SdFat.h
            ${CMAKE_CURRENT_LIST_DIR}/utility/SdInfo.h
    )
    target_include_directories(LIB_SD
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
            ${MCU_VARIANT_PATH}
    )
    target_link_libraries(LIB_SD 
        LIB_ARDUINO_CORE
        )
endif()