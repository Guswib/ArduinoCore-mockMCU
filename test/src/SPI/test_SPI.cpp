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
#include <SPI.h>
#include <iostream>
/**************************************************************************************
 * TEST CODE
 **************************************************************************************/
#include <StreamMock.h>

//std::ostream &out=std::cout;

TEST_CASE ("Testing SPI", "[SPI-begin-01]")
{
  SPI.begin();
  StreamMock mock;
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  int a=Serial.available();
  Serial.print("test before");
  Serial.println(a);
  while(Serial.available()) Serial.read();
  SPI.transfer(1);
  SPI.transfer(2);
  SPI.transfer(3);
  SPI.transfer(4);
  SPI.transfer(5);
  SPI.endTransaction();
  a=Serial.available();
  Serial.print("test done");
  Serial.println(a);
  a= SPI.sizeStream();
  Serial.print("Check stream: ");
  for(int i=0; i<a;i++){
    Serial.print(SPI.readStream(),HEX);
  }


  //out.write(tmp,a);

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

TEST_CASE ("Testing SPI-2", "[SPI-begin-02]")
{
  SPI.begin();
  StreamMock mock;
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  int a=Serial.available();
  Serial.print("test before");
  Serial.println(a);
  while(Serial.available()) Serial.read();
  SPI.transfer(1);
  SPI.transfer(2);
  SPI.transfer(3);
  SPI.transfer(4);
  SPI.transfer(5);
  SPI.endTransaction();
  a=Serial.available();
  Serial.print("test done");
  Serial.println(a);
  //out.write(tmp,a);
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