#ifndef __ARDUINO__H__
#define __ARDUINO__H__

#include "api/ArduinoAPI.h"

#include "pins_arduino.h"

#include <api/itoa.h>
#include <api/deprecated-avr-comp/avr/dtostrf.h>
#include <strings.h>


#include "UART.h"

#define Serial _UART0_
#define Serial1 _UART1_
#define Serial2 _UART2_
#define Serial3 _UART3_
//#define Serial4 _UART4_

#endif //__ARDUINO__H__
