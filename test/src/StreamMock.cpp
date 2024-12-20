//#pragma once
/*
 * Copyright (c) 2020 Arduino.  All rights reserved.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <StreamMock.h>
#include <iostream>
/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/
  std::istream &in=std::cin;
  std::ostream &out=std::cout;
  //std::string buffered;


void StreamMock::operator << (char const * str)
{
  for (size_t c = 0; c < strlen(str); c++)
    _stream.push_back(str[c]);
}

size_t StreamMock::write(uint8_t ch)
{ 
  _stream.push_back(static_cast<char>(ch));
  char tmp[1];
  tmp[0]=ch;
  out.write(tmp,1);
  return 1;
}
//GW ADDED
size_t StreamMock::write(uint8_t buf[], uint8_t leng)
{
  for(int i=0;i<leng;i++)
    write(buf[i]);
  return leng;
}


int StreamMock::available()
{
  return _stream.size();
}

int StreamMock::read()
{
  if (available() == 0)
    return -1;

  /* Extract first/oldest element. */
  char const c = _stream.at(0);
  /* Erase first/oldest element. */
  _stream.pop_front();

  return c;
}

int StreamMock::peek()
{
  if (available() == 0)
    return -1;

  return _stream.at(0);
}

//StreamMock Serial;
//StreamMock Serial1;


