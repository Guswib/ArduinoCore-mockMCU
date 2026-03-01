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
  int a = analogRead(A0);
  
}


TEST(Testing_ADC, begin)
{
  int a = analogRead(A0);
  
}



}