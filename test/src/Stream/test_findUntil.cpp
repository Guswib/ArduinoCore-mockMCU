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
#include <StreamMock.h>

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

TEST(Testing_Stream, Stream_findUntil_01)
{
  StreamMock mock;

 
   
      mock << "This is a : test string";
      EXPECT_TRUE(mock.findUntil("test", ": ") == false);
      EXPECT_TRUE(mock.readString() == arduino::String("test string"));
     StreamMock mock1;

      mock1 << "This is a test : string";
      EXPECT_TRUE(mock1.findUntil("test", ": ") == true);
      EXPECT_TRUE(mock1.readString() == arduino::String(" : string"));
      StreamMock mock2;

      mock2 << "This is a test string";
      EXPECT_TRUE(mock2.findUntil("test", ": ") == true);
      EXPECT_TRUE(mock2.readString() == arduino::String(" string"));
    
  

 
}
