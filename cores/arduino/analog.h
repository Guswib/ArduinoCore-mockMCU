
#ifndef __ARDUINO_ANALOG_H__
#define __ARDUINO_ANALOG_H__

#include "Arduino.h"
#include "StreamMock.h"

extern int analog_write_values[];
extern int analogReadResolution_value;
extern int analogReference_value;
extern StreamMock MOCKStream_analogIO;

int analogReadResolution(int res);
int analogRead(int pin);

void analogReference(uint8_t mode);

void analogWrite(uint8_t pin, int val);

#endif
