/*
 * Copyright (c) 2020 Arduino.  All rights reserved.
 */

#ifndef PRINT_MOCK_H_
#define PRINT_MOCK_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <string>

#include <api/Print.h>
#include <api/ArduinoAPI.h>


#include <stddef.h>
#include <stdint.h>
#include <string.h>
//#if !defined(ARDUINO)
#include <iostream>
#include <sstream>


/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class PrintMock : public arduino::Print
{
public:
  std::string _str;
  virtual size_t write(uint8_t b) override;
  void mock_setWriteError() { setWriteError(); }
  void mock_setWriteError(int err) { setWriteError(err); }
};


struct CppStreamPrint : PrintMock {
  std::ostream &out;
  CppStreamPrint(std::ostream &_out = std::cout);
  size_t write(uint8_t c);
  size_t write(const uint8_t *buffer, size_t size);
  int availableForWrite();
};




#endif /* PRINT_MOCK_H_ */
