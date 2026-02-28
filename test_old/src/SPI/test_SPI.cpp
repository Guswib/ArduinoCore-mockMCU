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
  SPI.transfer(0x65);
  SPI.transfer(0x66);
  SPI.transfer(0x67);
  SPI.transfer(0x68);
  SPI.transfer(0x69);
  SPI.endTransaction();
  a=Serial.available();
  Serial.print("test done: ");
  Serial.println(a);
  a= SPI.sizeStream();
  char SPI_stream[a+5];
  Serial.print("Check stream: ");
  for(int i=0; i<a;i++){
    uint8_t c = SPI.readStream();
    Serial.print(" ");
    Serial.print(c,HEX);
    SPI_stream[i]=c;
    REQUIRE(i+0x65 == c);
  }
  SPI_stream[a]='\0';
  Serial.println("");
  Serial.println(SPI_stream);
  //out.write(tmp,a);

  
    mock << "This is a test string";
    
   // REQUIRE(arduino::String("12345") == arduino::String(SPI_stream));
  
   
}

TEST_CASE ("Testing SPI-2", "[SPI-begin-02]")
{
  SPI.begin();
  StreamMock mock;
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  int a=Serial.available();
  Serial.print("test before3: ");
  Serial.println(a);
  while(Serial.available()) Serial.read();
  SPI.transfer(1);
  SPI.transfer(2);
  SPI.transfer(3);
  SPI.transfer(4);
  SPI.transfer(5);
  SPI.endTransaction();
  a=Serial.available();
  Serial.print("test done3: ");
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