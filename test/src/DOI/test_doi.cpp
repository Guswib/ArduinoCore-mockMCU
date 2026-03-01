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
#include <HW_IO.h>

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
#include <StreamMock.h>

//std::ostream &out=std::cout;
namespace {


TEST(Testing_DIO, digitalRead)
{
  HW_pinStatus[0] = HIGH;
  int a = digitalRead(0);
  EXPECT_EQ(a, HIGH);
  HW_pinStatus[0] = LOW;
  int b = digitalRead(0);
  EXPECT_EQ(b, LOW);
}


TEST(Testing_DIO, digitalWrite)
{
  HW_pinStatus[0] = LOW;
  digitalWrite(0, HIGH);
  PinStatus  a = HW_pinStatus[0];
  EXPECT_EQ(a, HIGH);
  digitalWrite(0, LOW);
  PinStatus  b = HW_pinStatus[0];
  EXPECT_EQ(b, LOW);
}

TEST(Testing_DIO, pinMode)
{
  HW_pinMode[0] = INPUT;
  
  pinMode(0, OUTPUT);
  PinMode  a = HW_pinMode[0];
  EXPECT_EQ(a, OUTPUT);
  
  pinMode(0, INPUT_PULLUP);
  PinMode  b = HW_pinMode[0];
  EXPECT_EQ(b, INPUT_PULLUP);

  pinMode(0,  INPUT);
  PinMode  c = HW_pinMode[0];
  EXPECT_EQ(c, INPUT);
}

}