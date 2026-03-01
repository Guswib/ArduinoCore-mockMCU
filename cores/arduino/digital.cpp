#include "Arduino.h"

PinMode HW_pinMode[NUM_DIGITAL_PINS];
PinStatus HW_pinStatus[NUM_DIGITAL_PINS];	


void pinMode(pin_size_t pin, const PinMode mode) {
	switch (mode) {
		case INPUT:
		case INPUT_PULLDOWN: // TODO: document the INPUT_PULLDOWN is unavailable
			//R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_INPUT);
			break;
		case INPUT_PULLUP:
			//R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_INPUT | IOPORT_CFG_PULLUP_ENABLE);
			break;
		case OUTPUT:
			//R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_OUTPUT);
			break;
		case OUTPUT_OPENDRAIN:
			//R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PMOS_ENABLE);
			break;
		}
	if(pin < NUM_DIGITAL_PINS) {
		HW_pinMode[pin] = mode;
	}
}

void digitalWrite(pin_size_t pin, PinStatus val) {
	if(pin >= NUM_DIGITAL_PINS) return;
	HW_pinStatus[pin] = val;
	//R_IOPORT_PinWrite(NULL, g_pin_cfg[pin].pin, val == LOW ? BSP_IO_LEVEL_LOW : BSP_IO_LEVEL_HIGH);
}

PinStatus digitalRead(pin_size_t pin) {
	//bsp_io_level_t ret;
	//R_IOPORT_PinRead(NULL, g_pin_cfg[pin].pin, &ret);
	if(pin >= NUM_DIGITAL_PINS) return LOW;
	else
		return HW_pinStatus[pin];
}