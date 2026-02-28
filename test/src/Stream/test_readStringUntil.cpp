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
#include <MillisFake.h>
#include <StreamMock.h>
#include <iostream>
/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

 namespace {

TEST(readStringUntil, Stream_readStringUntil_01)
{
  StreamMock mock;
  mock.setTimeout(10);
  millis_autoOn();
  mock << "This is test! lorem ipsum lalala";

  EXPECT_TRUE(mock.readStringUntil('!') == arduino::String("This is test"));
}

TEST(readStringUntil, Stream_readStringUntil_02)

{
  StreamMock mock;
  mock.setTimeout(10);
  millis_autoOn();
  mock << "This is test ... lorem ipsum lalala";

  EXPECT_TRUE(mock.readStringUntil('!') == arduino::String("This is test ... lorem ipsum lalala"));
}

}
