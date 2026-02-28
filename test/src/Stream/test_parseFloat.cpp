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

#include <float.h>

using namespace arduino;

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/

namespace {
  TEST(parseFloat, Stream_parseFloat_01)
  {
    StreamMock mock;


      mock << "12";
      EXPECT_TRUE(mock.parseFloat() == 12.0f);
  
      mock << "12.34";
      EXPECT_TRUE(mock.parseFloat() == 12.34f);
  
      mock << "-12.34";
      EXPECT_TRUE(mock.parseFloat() == -12.34f);
  
      mock << "abcdef12.34";
      EXPECT_TRUE(mock.parseFloat() == 12.34f);
    
    
      mock << "\r\n\t 12.34";
      EXPECT_TRUE(mock.parseFloat() == 12.34f);
    
    
      mock << "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870064";
      EXPECT_NEAR(mock.parseFloat(), 3.14159265f, 0.00000001f);
    
  
      mock << "602200000000000000000000.00";
      //EXPECT_TRUE(mock.parseFloat() == Approx(6.022e23f));
      EXPECT_NEAR(mock.parseFloat(), 6.022e23f, 1e20f);
    
  }

  TEST(parseFloat,Stream_parseFloat_02)
  {
    StreamMock mock;


    mock << "12.34";
    EXPECT_TRUE(mock.parseFloat(SKIP_NONE) == 12.34f);
    EXPECT_TRUE(mock.readString() == arduino::String(""));

    StreamMock mock1;

    mock1 << "abcdef12.34";
    EXPECT_TRUE(mock1.parseFloat(SKIP_NONE) == 0);
    EXPECT_TRUE(mock1.readString() == arduino::String("abcdef12.34"));

    StreamMock mock2;

    mock2 << "\r\n\t 12.34";
    EXPECT_TRUE(mock2.parseFloat(SKIP_NONE) == 0);
    EXPECT_TRUE(mock2.readString() == arduino::String("\r\n\t 12.34"));
    
  }

  TEST(parseFloat,Stream_parseFloat_03)
  {
    StreamMock mock;

      mock << "\r\n\t 12.34";
      EXPECT_TRUE(mock.parseFloat(SKIP_WHITESPACE) == 12.34f);
      EXPECT_TRUE(mock.readString() == arduino::String(""));
    
  }


  TEST(parseFloat,Stream_parseFloat_04)
  {
    StreamMock mock;
      mock << "12.34";
      EXPECT_TRUE(mock.parseFloat(SKIP_ALL, 'a') == 12.34f);
      EXPECT_TRUE(mock.readString() == arduino::String(""));
    StreamMock mock1;
      mock1 << "12a.3a4a";
      EXPECT_TRUE(mock1.parseFloat(SKIP_ALL, 'a') == 12.34f);
      EXPECT_TRUE(mock1.readString() == arduino::String(""));
  StreamMock mock2;
      mock2 << "1bed234";
      EXPECT_TRUE(mock2.parseFloat(SKIP_ALL, 'a') == 1.0f);
      EXPECT_TRUE(mock2.readString() == arduino::String("bed234"));
    

  }

}