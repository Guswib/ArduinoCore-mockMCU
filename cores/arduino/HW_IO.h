
#ifndef __ARDUINO_HWIO_H__
#define __ARDUINO_HWIO_H__

#include "api/ArduinoAPI.h"
#include "StreamMock.h"

#include "api/Common.h"


extern int HW_analogWrite[];
extern int HW_analogReadResolution_value;
extern int HW_analogReference_value;

extern StreamMock MOCKStream_analogIO;

extern PinMode HW_pinMode[];
extern PinStatus HW_pinStatus[];	


//int analogReadResolution(int res);
//int analogRead(int pin);

//void analogReference(uint8_t mode);

//void analogWrite(uint8_t pin, int val);

#endif
