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
#include <api/Common.h>

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
#include <StreamMock.h>

//std::ostream &out=std::cout;
namespace {

TEST(Testing_ADC, ini)
{
  #ifdef HOST
    std::cout << "HOST IS DEFINED" << std::endl;
  #else
    std::cout << "HOST IS NOT DEFINED" << std::endl; 
  #endif

  #ifdef __cplusplus
      std::cout << "C++ IS DEFINED" << std::endl; 
  #else
    std::cout << "C++ IS NOT DEFINED" << std::endl; 
  #endif
 
  
}


TEST(Testing_ADC, analogRead)
{
  MOCKStream_analogIO.write(150);
  MOCKStream_analogIO.write(200);
  MOCKStream_analogIO.write(250);
  MOCKStream_analogIO.write(50);
  MOCKStream_analogIO.println();

  
  uint8_t a = analogRead(A0);
  EXPECT_EQ(a, 150);
  uint8_t b = analogRead(A0);
  EXPECT_EQ(b, 200);
  uint8_t c = analogRead(A0);
  EXPECT_EQ(c, 250);
  uint8_t d = analogRead(A0);
  EXPECT_EQ(d, 50);
  analogRead(A0);
  //uint8_t e = analogRead(A0);
  //Serial.println(e);
  //Serial.println(analogRead(A0));
  //EXPECT_TRUE(e > 50);
}

TEST(Testing_ADC, analogWrite)
{
  HW_analogWrite[0] = 0;
  analogWrite(A0, 150);
  int a = HW_analogWrite[0];
  EXPECT_EQ(a, 150);
  
  analogWrite(A0, 200);
  int b = HW_analogWrite[0];
  EXPECT_EQ(b, 200);
  MOCKStream_analogIO.println();
}


}