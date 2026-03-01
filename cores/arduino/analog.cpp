
#include "Arduino.h"

#include "api/Common.h"


int HW_analogWrite[NUM_ANALOG_OUTPUTS];
int HW_analogReference_value = 0;
int HW_analogReadResolution_value = 10;


StreamMock MOCKStream_analogIO;

int analogRead(pin_size_t pinNumber) {
    int randNumber = random(100, 200);
    if(MOCKStream_analogIO.available())
        randNumber = MOCKStream_analogIO.read();
    
    return randNumber;
}

int analogReadResolution(int res) {
    HW_analogReadResolution_value = res;
  return 0;
}


void analogReference(uint8_t mode)
{
	// can't actually set the register here because the default setting
	// will connect AVCC and the AREF pin, which would cause a short if
	// there's something connected to AREF.
	HW_analogReference_value = mode;
}

void analogWrite(pin_size_t pinNumber, int value)
{
    MOCKStream_analogIO.write(value);
     if(pinNumber >= NUM_ANALOG_OUTPUTS) return;
    if(value < 0) value = 0;
    HW_analogWrite[pinNumber] = value;
}