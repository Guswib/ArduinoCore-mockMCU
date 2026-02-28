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

TEST(readBytesUntil, Stream_readBytesUntil_01)
  {
    StreamMock mock;
    //WHEN ("the stream is empty")
    //{
      char buf[32] = {0};
      EXPECT_TRUE(mock.readBytesUntil(' ', buf, sizeof(buf)) == 0);
    //}
  }
TEST(readBytesUntil, Stream_readBytesUntil_02)

  //WHEN ("the stream contains the termination character")
  {
      StreamMock mock;

    char buf[32] = {0};
    char const str[] = "some stream content";
    char const EXPECTED_STR[] = "some";
    mock << str;

    EXPECT_TRUE(mock.readBytesUntil(' ', buf, sizeof(buf)) == strlen("some"));
    EXPECT_TRUE(strncmp(buf, EXPECTED_STR, sizeof(buf)) == 0);
    EXPECT_TRUE(mock.readString() == arduino::String("stream content"));
  }

TEST(readBytesUntil, Stream_readBytesUntil_03)
  //WHEN ("the stream does not contain the termination character")
  {
      StreamMock mock;

    char buf[32] = {0};
    char const STR[] = "some stream content";
    mock << STR;

    EXPECT_TRUE(mock.readBytesUntil('!', buf, sizeof(buf)) == strlen(STR));
    EXPECT_TRUE(strncmp(buf, STR, sizeof(buf)) == 0);
    EXPECT_TRUE(mock.readString() == arduino::String(""));
  }


}
