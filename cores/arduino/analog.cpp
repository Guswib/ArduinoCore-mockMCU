
#include <Arduino.h>

#include "analog.h"

#include <api/Common.h>


int analog_write_values[16];
int analogReference_value = 0;
int analogReadResolution_value = 10;


StreamMock MOCKStream_analogIO;

int analogRead(int pin) {
    int randNumber = random(100, 200);
    if(MOCKStream_analogIO.available())
        randNumber = MOCKStream_analogIO.read();
    
    return randNumber;
}

int analogReadResolution(int res) {
    analogReadResolution_value = res;
  return 0;
}



void analogReference(uint8_t mode)
{
	// can't actually set the register here because the default setting
	// will connect AVCC and the AREF pin, which would cause a short if
	// there's something connected to AREF.
	analogReference_value = mode;
}

void analogWrite(uint8_t pin, int val)
{
    MOCKStream_analogIO.write(val);
     if(pin >= 16) return;
    if(val < 0) val = 0;
    analog_write_values[pin] = val;
}