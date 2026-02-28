/*
 * Copyright (c) 2020 Arduino.  All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <catch.hpp>

#include <Arduino.h>
#include <SPI.h>
#include <iostream>
/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
#include <StreamMock.h>

//std::ostream &out=std::cout;

TEST_CASE ("Testing ADC", "[ADC-begin-01]")
{
  int a =analogRead(A0);
  
}
