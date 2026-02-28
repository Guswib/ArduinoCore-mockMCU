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

 namespace {

TEST(timeout, Stream_setTimeout_01)
{
  StreamMock mock;

  mock.setTimeout(100);

  EXPECT_TRUE(mock.getTimeout() == 100);
}

}
