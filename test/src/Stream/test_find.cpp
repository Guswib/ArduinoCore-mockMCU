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
//#include <StreamMock.h>

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

namespace {
TEST(Testing_Stream, Stream_find_01)
{
  StreamMock mock;

 
  mock << "This is a test string";

    EXPECT_TRUE(mock.find("test") == true);
    EXPECT_TRUE(mock.readString() == arduino::String(" string"));

}
}


