if(NOT TARGET LIB_ETHERNET)
    add_library(LIB_ETHERNET STATIC "")
    target_sources(LIB_ETHERNET
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/Dhcp.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Dns.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Ethernet.cpp
            ${CMAKE_CURRENT_LIST_DIR}/EthernetClient.cpp
            ${CMAKE_CURRENT_LIST_DIR}/EthernetServer.cpp
            ${CMAKE_CURRENT_LIST_DIR}/EthernetUdp.cpp
            ${CMAKE_CURRENT_LIST_DIR}/socket.cpp
            ${CMAKE_CURRENT_LIST_DIR}/utility/w5100.cpp
            
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/Dhcp.h
            ${CMAKE_CURRENT_LIST_DIR}/Dns.h
            ${CMAKE_CURRENT_LIST_DIR}/Ethernet.h
            ${CMAKE_CURRENT_LIST_DIR}/EthernetClient.h
            ${CMAKE_CURRENT_LIST_DIR}/EthernetServer.h
            ${CMAKE_CURRENT_LIST_DIR}/EthernetUdp.h
            ${CMAKE_CURRENT_LIST_DIR}/utility/w5100.h
    )

    target_include_directories(LIB_ETHERNET
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
            ${MCU_VARIANT_PATH}
            ../SPI
    )
    target_link_libraries(LIB_ETHERNET 
        LIB_SPI
        LIB_ARDUINO_CORE
        )

endif()