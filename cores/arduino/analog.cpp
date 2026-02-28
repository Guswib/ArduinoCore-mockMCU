
#include <Arduino.h>

int analogRead(int pin) {
  return 0;
}

void analogReference(uint8_t mode)
{
	// can't actually set the register here because the default setting
	// will connect AVCC and the AREF pin, which would cause a short if
	// there's something connected to AREF.
	//analog_reference = mode;
}

void analogWrite(uint8_t pin, int val)
{
  //analogWrite(pin, val);
}