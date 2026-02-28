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

using namespace arduino;

namespace {

TEST(parseInt, Stream_parseInt_01)
{
  StreamMock mock;

//#WHEN ("A positive integer is contained in stream")
//  {
    mock << "1234";
    EXPECT_TRUE(mock.parseInt() == 1234);
//  }
//  WHEN ("A negative integer is contained in stream")
//  {

    mock << "-1234";
    EXPECT_TRUE(mock.parseInt() == -1234);
//  }
//  WHEN ("A integer is prepended by digits")
//  {
    mock << "abcdef1234";
    EXPECT_TRUE(mock.parseInt() == 1234);
//  }
//  WHEN ("A integer is prepended by whitespace chars")
//  {
    mock << "\r\n\t 1234";
    EXPECT_TRUE(mock.parseInt() == 1234);
//  }
}

TEST(parseInt, Stream_parseInt_02)
{
  StreamMock mock;

  //WHEN ("A positive integer is contained in stream")
  //{
    mock << "1234";
    EXPECT_TRUE(mock.parseInt(SKIP_NONE) == 1234);
    EXPECT_TRUE(mock.readString() == arduino::String(""));
  //}
  //WHEN ("A integer is prepended by digits")
  //{
    mock << "abcdef1234";
    EXPECT_TRUE(mock.parseInt(SKIP_NONE) == 0);
    EXPECT_TRUE(mock.readString() == arduino::String("abcdef1234"));
  //}
  //WHEN ("A integer is prepended by whitespace chars")
  //{
    mock << "\r\n\t 1234";
    EXPECT_TRUE(mock.parseInt(SKIP_NONE) == 0);
    EXPECT_TRUE(mock.readString() == arduino::String("\r\n\t 1234"));
  //}
}

TEST(parseInt, Stream_parseInt_03)
{
  StreamMock mock;

  //WHEN ("A integer is prepended by whitespace chars")
  //{
    mock << "\r\n\t 1234";
    EXPECT_TRUE(mock.parseInt(SKIP_WHITESPACE) == 1234);
    EXPECT_TRUE(mock.readString() == arduino::String(""));
  //}
}

TEST(parseInt, Stream_parseInt_04)
{
  StreamMock mock;

  //WHEN ("A positive integer is contained in stream")
  //{
    mock << "1234";
    EXPECT_TRUE(mock.parseInt(SKIP_ALL, 'a') == 1234);
    EXPECT_TRUE(mock.readString() == arduino::String(""));
  //}
  //WHEN ("A integer contains only ignore char values")
  //{
    mock << "12a3a4a";
    EXPECT_TRUE(mock.parseInt(SKIP_ALL, 'a') == 1234);
    EXPECT_TRUE(mock.readString() == arduino::String(""));
  //}
  //WHEN ("A integer contains other than ignore chars")
  //{
    mock << "1bed234";
    EXPECT_TRUE(mock.parseInt(SKIP_ALL, 'a') == 1);
    EXPECT_TRUE(mock.readString() == arduino::String("bed234"));
  //}
}
}