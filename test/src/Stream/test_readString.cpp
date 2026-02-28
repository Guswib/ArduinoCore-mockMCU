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

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
namespace {
TEST(readString, Stream_readString_01)
{
  StreamMock mock;
  mock.setTimeout(10);
  millis_autoOn();
  mock << "This is test stream content";

  EXPECT_TRUE(mock.readString() == arduino::String("This is test stream content"));
}
}