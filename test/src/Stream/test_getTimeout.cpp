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

TEST(getTimeout, Stream_getTimeout_01)
{
  StreamMock mock;
  EXPECT_TRUE(mock.getTimeout() == 1000);
}
