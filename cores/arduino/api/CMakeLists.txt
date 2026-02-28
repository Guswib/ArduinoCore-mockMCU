# Check if a variable named 'MY_VARIABLE' is set
if(DEFINED PATH_TO_ARDUINO_API)
 #   message("       API: PATH_TO_ARDUINO_API is set. Value: ${PATH_TO_ARDUINO_API}")
else()
    set(PATH_TO_ARDUINO_API "${CMAKE_CURRENT_LIST_DIR}")
    message("       API: PATH_TO_ARDUINO_API is not set. Defaulting to: ${PATH_TO_ARDUINO_API}")
    message("       API: PATH_TO_ARDUINO_API is not set. Defaulting to: ${CMAKE_CURRENT_LIST_DIR}")

endif()


set(api_h_files
            ${PATH_TO_ARDUINO_API}/ArduinoAPI.h
            ${PATH_TO_ARDUINO_API}/Binary.h
            ${PATH_TO_ARDUINO_API}/CanMsg.h
            ${PATH_TO_ARDUINO_API}/Client.h  
            ${PATH_TO_ARDUINO_API}/Common.h  
            ${PATH_TO_ARDUINO_API}/Compat.h  
            ${PATH_TO_ARDUINO_API}/DMAPool.h  
            ${PATH_TO_ARDUINO_API}/HardwareCAN.h  
            ${PATH_TO_ARDUINO_API}/HardwareI2C.h  
            ${PATH_TO_ARDUINO_API}/HardwareSerial.h
            ${PATH_TO_ARDUINO_API}/HardwareSPI.h
            ${PATH_TO_ARDUINO_API}/Interrupts.h  
            ${PATH_TO_ARDUINO_API}/IPAddress.h
            ${PATH_TO_ARDUINO_API}/itoa.h 
            ${PATH_TO_ARDUINO_API}/PluggableUSB.h
            ${PATH_TO_ARDUINO_API}/Print.h
            ${PATH_TO_ARDUINO_API}/Printable.h
            ${PATH_TO_ARDUINO_API}/RingBuffer.h
            ${PATH_TO_ARDUINO_API}/Server.h
            ${PATH_TO_ARDUINO_API}/Stream.h
            ${PATH_TO_ARDUINO_API}/String.h
            ${PATH_TO_ARDUINO_API}/Udp.h
            ${PATH_TO_ARDUINO_API}/USBAPI.h

            ${PATH_TO_ARDUINO_API}/deprecated-avr-comp/avr/dtostrf.h
            ${PATH_TO_ARDUINO_API}/deprecated-avr-comp/avr/interrupt.h
            ${PATH_TO_ARDUINO_API}/deprecated-avr-comp/avr/pgmspace.h

) # Creates a list: a;b;c

target_sources(LIB_ARDUINO_CORE
        PUBLIC
        FILE_SET HEADERS    
        FILES ${api_h_files}
     )

if(TARGET LIB_ARDUINO_CORE)
    add_library(LIB_ARDUINO_CORE_API INTERFACE "")
  #  target_sources(LIB_ARDUINO_CORE
  #      INTERFACE
  #          ${api_h_files}
  #  )
endif()


if(TARGET LIB_ARDUINO_CORE)
    #add_library(LIB_ARDUINO_CORE_API STATIC "")
#target_compile_options(LIB_ARDUINO_CORE_API PRIVATE "-include" "cstring")
#   target_compile_options(LIB_ARDUINO_CORE_API PRIVATE "-include" "String.h")

    target_include_directories(LIB_ARDUINO_CORE
        PUBLIC 
            "${CMAKE_CURRENT_LIST_DIR}/deprecated-avr-comp"
   #         ${PATH_TO_ARDUINO_API}
    )
#target_compile_definitions(LIB_ARDUINO_CORE_API PUBLIC __AVR__)


target_sources(LIB_ARDUINO_CORE
        PRIVATE
            #${PATH_TO_ARDUINO_API}/Print.cpp  

            ${PATH_TO_ARDUINO_API}/CanMsg.cpp  
            ${PATH_TO_ARDUINO_API}/CanMsgRingbuffer.cpp  
            ${PATH_TO_ARDUINO_API}/Common.cpp  
            ${PATH_TO_ARDUINO_API}/IPAddress.cpp  
            ${PATH_TO_ARDUINO_API}/PluggableUSB.cpp  
            ${PATH_TO_ARDUINO_API}/Print.cpp  
            ${PATH_TO_ARDUINO_API}/Stream.cpp    
            ${PATH_TO_ARDUINO_API}/String.cpp        
    )

 

endif()


