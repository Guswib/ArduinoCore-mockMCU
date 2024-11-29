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

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>
#include <api/HardwareSPI.h>
#include <api/Print.h>

#ifndef USE_MALLOC_FOR_IRQ_MAP
#define USE_MALLOC_FOR_IRQ_MAP  0
#endif

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
// #define SPI_HAS_TRANSACTION 1

// SPI_HAS_NOTUSINGINTERRUPT means that SPI has notUsingInterrupt() method
#define SPI_HAS_NOTUSINGINTERRUPT 1

#define SS 1
#define MOSI 1
#define MISO 2
#define SCK 1

#define PIN_SPI_SCK 100
#define PIN_SPI_SS SS

#define MUX_SPI 0


#define SPI_MODE0           ( 1 )
#define SPI_MODE1           ( 2 )
#define SPI_MODE2           ( 3 )
#define SPI_MODE3           ( 4 )

#define SPI_MODE_MASK       ( 1   )
#define SPI_CLOCK_MASK      ( 2  )
#define SPI_2XCLOCK_MASK    ( 3  )

#define SPI_INTERRUPT_DISABLE     0
#define SPI_INTERRUPT_ENABLE      1

#ifndef EXTERNAL_NUM_INTERRUPTS
#define EXTERNAL_NUM_INTERRUPTS   NUM_TOTAL_PINS
#endif

class SPISettingsMOCK : public arduino::SPISettings {
  public:
  SPISettingsMOCK(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
    if (__builtin_constant_p(clock)) {
      init_AlwaysInline(clock, bitOrder, dataMode);
    } else {
      init_MightInline(clock, bitOrder, dataMode);
    }
  }

  // Default speed set to 4MHz, SPI mode set to MODE 0 and Bit order set to MSB first.
  SPISettingsMOCK() { init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0); }

  SPISettingsMOCK(SPISettings& x) { SPISettingsMOCK(x.getClockFreq(), x.getBitOrder(), x.getDataMode()); }

  private:
  void init_MightInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
    init_AlwaysInline(clock, bitOrder, dataMode);
  }

  void init_AlwaysInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) __attribute__((__always_inline__)) {
    // Clock settings are defined as follows. Note that this shows SPI2X
    // inverted, so the bits form increasing numbers. Also note that
    // fosc/64 appears twice.  If FOSC is 16 Mhz
    // PRESC[1:0]  ~SPI2X Freq
    //   0    0     0   fosc/2    8.00 MHz 
    //   0    0     1   fosc/4    4.00 MHz
    //   0    1     0   fosc/8    2.00 MHz
    //   0    1     1   fosc/16   1.00 MHz
    //   1    0     0   fosc/32   500  kHz
    //   1    0     1   fosc/64   250  kHz
    //   1    1     0   fosc/64   250  kHz
    //   1    1     1   fosc/128  125  kHz

    // We find the fastest clock that is less than or equal to the
    // given clock rate. The clock divider that results in clock_setting
    // is 2 ^^ (clock_div + 1). If nothing is slow enough, we'll use the
    // slowest (128 == 2 ^^ 7, so clock_div = 6).
    uint8_t clockDiv;
    
    // When the clock is known at compiletime, use this if-then-else
    // cascade, which the compiler knows how to completely optimize
    // away. When clock is not known, use a loop instead, which generates
    // shorter code.
    
    /*  This is no longer the case since, F_CPU_CORRECTED is variable */
    /*  set at run time.                                             */

    uint32_t clockSetting = 0; 
    
    //clockSetting = F_CPU_CORRECTED / 2;
    clockSetting =160000L;
    clockDiv = 0;
    while ((clockDiv < 6) && (clock < clockSetting)) {
      clockSetting /= 2;
      clockDiv++;
    }
        
    // Compensate for the duplicate fosc/64,
    // should be fosc/128 if clockdiv 6.
    if (clockDiv == 6)
    {
      clockDiv++;
    }
        
    // Invert the SPI2X bit
    clockDiv ^= 0x1;
        
    /* Pack into the SPISettings::ctrlb class */
    /* Set mode, disable master slave select, and disable buffering. */
    /* dataMode is register correct, when using SPI_MODE defines     */
    ctrlb = 2;
                
    /* Get Clock related values.*/
    uint8_t clockDiv_mult = (clockDiv & 0x1);
    uint8_t clockDiv_pres = (clockDiv >> 1);
        
    /* Pack into the SPISettings::ctrlb class     */
    /* Set Prescaler, x2, SPI to Master, and Bit Order. */
    
    ctrla = 1;
    
  }
  /* member variables containing the desired SPI settings */
  uint8_t ctrla;
  uint8_t ctrlb;
  friend class SPIClassMegaAVR;
};

class SPIClassMOCK : public arduino::HardwareSPI {
  public:
  SPIClassMOCK(uint8_t uc_pinMISO, uint8_t uc_pinSCK, uint8_t uc_pinMOSI, uint8_t uc_pinSS, uint8_t uc_mux);

  byte transfer(uint8_t data);
  uint16_t transfer16(uint16_t data);
  void transfer(void *buf, size_t count);

  // Transaction Functions
  void usingInterrupt(int interruptNumber);
  void notUsingInterrupt(int interruptNumber);
  void beginTransaction(SPISettingsMOCK settings);
  void beginTransaction(SPISettings settings) {
    beginTransaction(SPISettingsMOCK(settings));
  }
  void endTransaction(void);

  void begin();
  void end();

  void setBitOrder(BitOrder order);
  void setDataMode(uint8_t uc_mode);
  void setClockDivider(uint8_t uc_div);

  private:

  void init();
  void config(SPISettingsMOCK settings);
  void config(SPISettings settings) {
    config(SPISettingsMOCK(settings));
  }

  // These undocumented functions should not be used.  SPI.transfer()
  // polls the hardware flag which is automatically cleared as the
  // AVR responds to SPI's interrupt
  inline void attachInterrupt() { ; }
  inline void detachInterrupt() { ; }

  void detachMaskedInterrupts();
  void reattachMaskedInterrupts();

  uint8_t _uc_pinMiso;
  uint8_t _uc_pinMosi;
  uint8_t _uc_pinSCK;
  uint8_t _uc_pinSS;
  uint8_t _uc_mux;

  bool initialized;
  uint8_t interruptMode;
  char interruptSave;
  uint32_t interruptMask_lo;
  uint32_t interruptMask_hi;

  uint8_t* irqMap = NULL;
  };

#define SPIClass SPIClassMOCK

#if SPI_HOWMANY > 0
  extern SPIClass SPI;
#endif

#define SPI_CLOCK_DIV2      2
#define SPI_CLOCK_DIV4      4
#define SPI_CLOCK_DIV8      8
#define SPI_CLOCK_DIV16     16
#define SPI_CLOCK_DIV32     32
#define SPI_CLOCK_DIV64     64
#define SPI_CLOCK_DIV128    128

#endif
