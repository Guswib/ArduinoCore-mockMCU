#ifndef __SOFTWARE_SERIAL_H__
#define __SOFTWARE_SERIAL_H__

#include <Arduino.h>

#include "mock/StreamMock.h"


class SoftwareSerial : public Stream, public Printable {
    private:
        uint8_t _tx_pin, _rx_pin;
      uint32_t _sconfig=0;
         StreamMock mockstream;
    public:
        using Print::write;
        SoftwareSerial(uint8_t rx_pin, uint8_t tx_pin, size_t bufsize=1024);
        virtual ~SoftwareSerial();
        size_t printTo(Print& p){return 5;};
        int begin(uint32_t baudrate, uint32_t sconfig=SERIAL_8N1, bool inverted=false);
        virtual int read();
        int peek();
        virtual size_t write(uint8_t byte);
        virtual int available();
        int listen(){return 0;};
        int isListening(){return 1;};
};


#endif  //__SOFTWARE_SERIAL_H__