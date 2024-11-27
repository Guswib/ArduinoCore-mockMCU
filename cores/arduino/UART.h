/*
  UART.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#pragma once

#include <inttypes.h>
#include "api/HardwareSerial.h"
#include "pins_arduino.h"
#include "StreamMock.h"


using namespace arduino;

// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
// NOTE: a "power of 2" buffer size is reccomended to dramatically
//       optimize all the modulo operations for ring buffers.
// WARNING: When buffer sizes are increased to > 256, the buffer index
// variables are automatically increased in size, but the extra
// atomicity guards needed for that are not implemented. This will
// often work, but occasionally a race condition can occur that makes
// Serial behave erratically. See https://github.com/arduino/Arduino/issues/2405

//#if !defined(SERIAL_TX_BUFFER_SIZE)



#if !defined(SERIAL_TX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_TX_BUFFER_SIZE 16
#else
#define SERIAL_TX_BUFFER_SIZE 64
#endif
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_RX_BUFFER_SIZE 16
#else
#define SERIAL_RX_BUFFER_SIZE 64
#endif
#endif
#if (SERIAL_TX_BUFFER_SIZE>256)
typedef uint16_t tx_buffer_index_t;
#else
typedef uint8_t tx_buffer_index_t;
#endif
#if  (SERIAL_RX_BUFFER_SIZE>256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif



#define USART_CMODE_ASYNCHRONOUS_gc 1
#define USART_CHSIZE_5BIT_gc 0



/* Universal Synchronous and Asynchronous Receiver and Transmitter */

typedef  uint8_t register8_t;
typedef  uint16_t register16_t;
typedef  uint32_t register32_t;

#define _WORDREGISTER(regname) __extension__ union { register16_t regname; struct { register8_t regname##L; register8_t regname##H; }; }

typedef struct USART_struct
{
    register8_t RXDATAL;  /* Receive Data Low Byte */
    register8_t RXDATAH;  /* Receive Data High Byte */
    register8_t TXDATAL;  /* Transmit Data Low Byte */
    register8_t TXDATAH;  /* Transmit Data High Byte */
    register8_t STATUS;  /* Status */
    register8_t CTRLA;  /* Control A */
    register8_t CTRLB;  /* Control B */
    register8_t CTRLC;  /* Control C */
    _WORDREGISTER(BAUD);  /* Baud Rate */
    register8_t CTRLD;  /* Control D */
    register8_t DBGCTRL;  /* Debug Control */
    register8_t EVCTRL;  /* Event Control */
    register8_t TXPLCTRL;  /* IRCOM Transmitter Pulse Length Control */
    register8_t RXPLCTRL;  /* IRCOM Receiver Pulse Length Control */
    register8_t reserved_1[1];
} USART_t;

class UartClass : public HardwareSerial
{
     
  protected:
    StreamMock mockstream;
   USART_t * const _hwserial_module;

     uint8_t const _hwserial_rx_pin;
     uint8_t const _hwserial_tx_pin;

     uint8_t const _uart_mux;

    // Has any byte been written to the UART since begin()
    bool _written;

     rx_buffer_index_t _rx_buffer_head;
     rx_buffer_index_t _rx_buffer_tail;
     tx_buffer_index_t _tx_buffer_head;
     tx_buffer_index_t _tx_buffer_tail;

     uint8_t _hwserial_dre_interrupt_vect_num;
     uint8_t _hwserial_dre_interrupt_elevated;
     uint8_t _prev_lvl1_interrupt_vect;

    // Don't put any members after these buffers, since only the first
    // 32 bytes of this struct can be accessed quickly using the ldd
    // instruction.
    unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
    unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

  public:
    
    //inline UartClass(volatile USART_t *hwserial_module, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t dre_vect_num, uint8_t uart_mux);
    UartClass(
         USART_t *hwserial_module,
         uint8_t hwserial_rx_pin,
         uint8_t hwserial_tx_pin,
         uint8_t hwserial_dre_interrupt_vect_num,
         uint8_t uart_mux) :
    _hwserial_module(hwserial_module),
    _hwserial_rx_pin(hwserial_rx_pin),
    _hwserial_tx_pin(hwserial_tx_pin),
    _uart_mux(uart_mux),
    _rx_buffer_head(0), _rx_buffer_tail(0),
    _tx_buffer_head(0), _tx_buffer_tail(0),
    _hwserial_dre_interrupt_vect_num(hwserial_dre_interrupt_vect_num),
    _hwserial_dre_interrupt_elevated(0),
    _prev_lvl1_interrupt_vect(0)
    {
    };
    virtual ~UartClass(){};

    void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
    void begin(unsigned long, uint16_t);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    virtual int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); };
    inline size_t write(long n) { return write((uint8_t)n); };
    inline size_t write(unsigned int n) { return write((uint8_t)n); };
    inline size_t write(int n) { return write((uint8_t)n); };
    using Print::write; // pull in write(str) and write(buf, size) from Print
    explicit operator bool() { return true; }
    bool operator! () { return true; };


    void bind(UartClass& ser) {bound = &ser; }

    // Interrupt handlers - Not intended to be called externally
    inline void _rx_complete_irq(void);
    void _tx_data_empty_irq(void);
  private:
    void _poll_tx_data_empty(void);
    UartClass* bound = NULL;
};

#if SERIAL_HOWMANY > 0
  extern UartClass _UART0_;
  #define HAVE_HWSERIAL0
#endif
#if SERIAL_HOWMANY > 1
  extern UartClass _UART1_;
  #define HAVE_HWSERIAL1
#endif
#if SERIAL_HOWMANY > 2
  extern UartClass _UART2_;
  #define HAVE_HWSERIAL2
#endif
#if SERIAL_HOWMANY > 3
  extern UartClass _UART3_;
  #define HAVE_HWSERIAL3
#endif


