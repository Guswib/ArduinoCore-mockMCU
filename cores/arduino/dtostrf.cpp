/*
 * Copyright (c) 2020 Arduino.  All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <api/deprecated-avr-comp/avr/dtostrf.h>

#include <stdlib.h>

/**************************************************************************************
 * FUNCTION IMPLEMENTATION
 **************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>

char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  asm(".global _printf_float");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
#pragma GCC diagnostic pop
}

//#include <api/deprecated-avr-comp/avr/dtostrf.c.impl>

#ifdef __cplusplus
} // extern "C"
#endif