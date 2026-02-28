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

TEST(readBytes,Stream_readBytes_01)
{
  StreamMock mock;

  //WHEN ("the stream is empty")
  //{
    char buf[32] = {0};
    EXPECT_TRUE(mock.readBytes(buf, sizeof(buf)) == 0);
  }

TEST(readBytes,Stream_readBytes_02)
  //WHEN ("the stream contains less data than we want to read")
{
   StreamMock mock;
    char buf[32] = {0};
    char const str[] = "some stream content";
    mock << str;

    EXPECT_TRUE(mock.readBytes(buf, sizeof(buf)) == strlen(str));
    EXPECT_TRUE(strncmp(buf, str, sizeof(buf)) == 0);
    EXPECT_TRUE(mock.readString() == arduino::String(""));
  }
TEST(readBytes,Stream_readBytes_03)

  //WHEN ("the stream contains more data than we want to read")
  {
  StreamMock mock;
    char buf[5] = {0};
    mock << "some stream content";
    char const EXPECTED_STR[] = "some ";

    EXPECT_TRUE(mock.readBytes(buf, sizeof(buf)) == 5);
    EXPECT_TRUE(strncmp(buf, EXPECTED_STR, sizeof(buf)) == 0);
    EXPECT_TRUE(mock.readString() == arduino::String("stream content"));
  }
}



