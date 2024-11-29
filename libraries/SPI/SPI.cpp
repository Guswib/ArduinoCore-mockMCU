/*
 * SPI Master library for Arduino Zero.
 * Copyright (c) 2015 Arduino LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "SPI.h"
#include <Arduino.h>

#include "StreamMock.h"


#define SPI_IMODE_NONE   0
#define SPI_IMODE_EXTINT 1
#define SPI_IMODE_GLOBAL 2

#define PIN_SPI_MISO MISO
#define PIN_SPI_MOSI MOSI


SPIClass::SPIClass(uint8_t uc_pinMISO, uint8_t uc_pinSCK, uint8_t uc_pinMOSI, uint8_t uc_pinSS, uint8_t uc_mux)
{
  initialized = false;

  // pins
  _uc_mux = uc_mux;
  _uc_pinMiso = uc_pinMISO;
  _uc_pinSCK = uc_pinSCK;
  _uc_pinMosi = uc_pinMOSI;
  _uc_pinSS = uc_pinSS;
}

void SPIClass::begin()
{
  init();

  //pinMode(_uc_pinMosi, OUTPUT);
  //pinMode(_uc_pinSCK, OUTPUT);
  // MISO is set to input by the controller

  // We don't need HW SS since salve/master mode is selected via registers

  config(DEFAULT_SPI_SETTINGS);
}

void SPIClass::init()
{
  if (initialized)
    return;
  interruptMode = SPI_IMODE_NONE;
  interruptSave = 0;
  interruptMask_lo = 0;
  interruptMask_hi = 0;
  initialized = true;
  Serial.println("SPI.ini is called");
}

void SPIClass::config(SPISettingsMOCK settings)
{
  //SPI0.CTRLA = settings.ctrla;
  //SPI0.CTRLB = settings.ctrlb;
}

void SPIClass::end()
{
  //SPI0.CTRLA &= ~(SPI_ENABLE_bm);
  initialized = false;
}

void SPIClass::usingInterrupt(int interruptNumber)
{
 ;
}

void SPIClass::notUsingInterrupt(int interruptNumber)
{
 ;
}

void SPIClass::detachMaskedInterrupts() {
 ;
 
}

void SPIClass::reattachMaskedInterrupts() {
 ;
}

void SPIClass::beginTransaction(SPISettingsMOCK settings)
{
  Serial.print("SPI.beginTransaction: ");
  ;
}

void SPIClass::endTransaction(void)
{
  Serial.println("  --endTransaction");
}

void SPIClass::setBitOrder(BitOrder order)
{
 ;
}

void SPIClass::setDataMode(uint8_t mode)
{
    ;
}

void SPIClass::setClockDivider(uint8_t div)
{
 ;                                       // write value 
}

byte SPIClass::transfer(uint8_t data)
{
  Serial.print(" ");
  Serial.print(data,HEX);
  return data;                             // read data back
}

uint16_t SPIClass::transfer16(uint16_t data) {
  union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } t;

  t.val = data;

 
  return data;
}

void SPIClass::transfer(void *buf, size_t count)
{
  for(size_t i=0;i<count,i++ ){
    transfer( buf[i]);
    }
}

if SPI_HOWMANY > 0
  SPIClass SPI (PIN_SPI_MISO,  PIN_SPI_SCK,  PIN_SPI_MOSI,  PIN_SPI_SS,  MUX_SPI);
#endif