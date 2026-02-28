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

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
#include <StreamMock.h>

namespace {

TEST(Testing_Serial, Serial_find_01)
{
 // WHEN ("'target' is contained in stream")

  StreamMock mock;
      mock << "This is a test string";

 
    EXPECT_TRUE(mock.find("test") == true);
    EXPECT_TRUE(mock.readString() == arduino::String(" string"));
}

 TEST(Testing_Serial, Serial_find_02)
 
  //WHEN ("'target' is not contained in stream")
  {
    StreamMock mock;
    EXPECT_TRUE(mock.find("test") == false);
    EXPECT_TRUE(mock.readString() == arduino::String(""));
}
}