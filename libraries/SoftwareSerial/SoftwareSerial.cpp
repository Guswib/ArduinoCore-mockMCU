
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "mock/StreamMock.h"

SoftwareSerial::SoftwareSerial(uint8_t rx_pin, uint8_t tx_pin, size_t bufsize)
{
   
    _tx_pin = tx_pin;
    _rx_pin = rx_pin;
}

SoftwareSerial::~SoftwareSerial()
{

}

int SoftwareSerial::begin(uint32_t baudrate, uint32_t sconfig, bool inverted)
{
    _sconfig=sconfig;
    return 0;
}

 


int SoftwareSerial::available(void)
{
    return mockstream.available();
 }

int SoftwareSerial::peek(void)
{
 
   return mockstream.peek();
}

int SoftwareSerial::read(void)
{
 
    return mockstream.read();
}

size_t  SoftwareSerial::write(uint8_t byte)
{
    return mockstream.write(byte);
}
