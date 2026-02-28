/*
 * Copyright (c) 2020 Arduino.  All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <gtest/gtest.h>
#include <Arduino.h>
#include <iostream>
/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
#include <StreamMock.h>

//std::ostream &out=std::cout;
namespace {

TEST(Testing_ADC, begin)
{
  int a =analogRead(A0);
  
}



}