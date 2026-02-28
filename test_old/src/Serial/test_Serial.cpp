/*
 * Copyright (c) 2020 Arduino.  All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <catch.hpp>

#include <Arduino.h>

/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
#include <StreamMock.h>

TEST_CASE ("Testing Serial", "[Serial-find-01]")
{
  //Serial.begin(9600);
  StreamMock mock;
  
  WHEN ("'target' is contained in stream")
  {
    mock << "This is a test string";
    
    REQUIRE(mock.find("test") == true);
    REQUIRE(mock.readString() == arduino::String(" string"));
  }
  WHEN ("'target' is not contained in stream")
  {
    mock << "This is a string";

    REQUIRE(mock.find("test") == false);
    REQUIRE(mock.readString() == arduino::String(""));
  }
}

