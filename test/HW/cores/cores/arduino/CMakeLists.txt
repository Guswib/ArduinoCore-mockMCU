if(NOT TARGET LIB_ARDUINO_CORE)
    add_library(LIB_ARDUINO_CORE STATIC "")

    target_sources(LIB_ARDUINO_CORE
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/digital.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/dtostrf.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/itoa.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART0.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART1.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART2.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/UART3.cpp  

            ${CMAKE_CURRENT_LIST_DIR}/api/CanMsg.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/api/CanMsgRingbuffer.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/api/Common.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/api/IPAddress.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/api/PluggableUSB.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/api/Print.cpp  
            ${CMAKE_CURRENT_LIST_DIR}/api/Stream.cpp    
            ${CMAKE_CURRENT_LIST_DIR}/api/String.cpp        
    
            
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/Arduino.h
            ${CMAKE_CURRENT_LIST_DIR}/UART.h

            ${CMAKE_CURRENT_LIST_DIR}/api/ArduinoAPI.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Binary.h
            ${CMAKE_CURRENT_LIST_DIR}/api/CanMsg.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Client.h  
            ${CMAKE_CURRENT_LIST_DIR}/api/Common.h  
            ${CMAKE_CURRENT_LIST_DIR}/api/Compat.h  
            ${CMAKE_CURRENT_LIST_DIR}/api/DMAPool.h  
            ${CMAKE_CURRENT_LIST_DIR}/api/HardwareCAN.h  
            ${CMAKE_CURRENT_LIST_DIR}/api/HardwareI2C.h  
            ${CMAKE_CURRENT_LIST_DIR}/api/HardwareSerial.h
            ${CMAKE_CURRENT_LIST_DIR}/api/HardwareSPI.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Interrupts.h  
            ${CMAKE_CURRENT_LIST_DIR}/api/IPAddress.h
            ${CMAKE_CURRENT_LIST_DIR}/api/itoa.h 
            ${CMAKE_CURRENT_LIST_DIR}/api/PluggableUSB.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Print.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Printable.h
            ${CMAKE_CURRENT_LIST_DIR}/api/RingBuffer.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Server.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Stream.h
            ${CMAKE_CURRENT_LIST_DIR}/api/String.h
            ${CMAKE_CURRENT_LIST_DIR}/api/Udp.h
            ${CMAKE_CURRENT_LIST_DIR}/api/USBAPI.h
            ${CMAKE_CURRENT_LIST_DIR}/api/WCharacter.h  

            ${CMAKE_CURRENT_LIST_DIR}/mock/MillisFake.h
            ${CMAKE_CURRENT_LIST_DIR}/mock/PrintableMock.h
            ${CMAKE_CURRENT_LIST_DIR}/mock/PrintMock.h
            ${CMAKE_CURRENT_LIST_DIR}/mock/StreamMock.h


    )
    target_include_directories(LIB_ARDUINO_CORE
        PUBLIC 
            ${CMAKE_CURRENT_LIST_DIR}
            ${MCU_VARIANT_PATH}
    )
    target_link_libraries(LIB_ARDUINO_CORE 
    PUBLIC ${LIB_MCU_VARIANT}
    )
    install(
        TARGETS LIB_ARDUINO_CORE
        RUNTIME_DEPENDENCIES
    )


endif()