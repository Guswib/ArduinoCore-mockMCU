/*
  UART.cpp - Hardware serial library for Wiring
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

  Created: 09.11.2017 07:29:09
  Author: M44307
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

#include "UART.h"


#include "StreamMock.h"

/* 
void serialEventRun(void)
{
#if defined(HAVE_HWSERIAL0)
    if (Serial0_available && serialEvent && Serial0_available()) serialEvent();
#endif
#if defined(HAVE_HWSERIAL1)
    if (Serial1_available && serialEvent1 && Serial1_available()) serialEvent1();
#endif
#if defined(HAVE_HWSERIAL2)
    if (Serial2_available && serialEvent2 && Serial2_available()) serialEvent2();
#endif
#if defined(HAVE_HWSERIAL3)
    if (Serial3_available && serialEvent3 && Serial3_available()) serialEvent3();
#endif
}
*/
// macro to guard critical sections when needed for large TX buffer sizes
#if (SERIAL_TX_BUFFER_SIZE > 256)
#define TX_BUFFER_ATOMIC ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
#define TX_BUFFER_ATOMIC
#endif





// Actual interrupt handlers //////////////////////////////////////////////////////////////





void UartClass::_tx_data_empty_irq(void)
{
   ;
}

// To invoke data empty "interrupt" via a call, use this method
void UartClass::_poll_tx_data_empty(void)
{
    ;
}

// Public Methods //////////////////////////////////////////////////////////////

void UartClass::begin(unsigned long baud, uint16_t config)
{
    // Make sure no transmissions are ongoing and USART is disabled in case begin() is called by accident
    // without first calling end()
    if(_written) {
        this->end();
    }

    // Setup port mux

    int32_t baud_setting = 0;

    //Make sure global interrupts are disabled during initialization
    //uint8_t oldSREG = SREG;

    baud_setting = 100;
    
    _written = false;

    int8_t sigrow_val = 0;
    baud_setting += (baud_setting * sigrow_val) / 1024;

}

void UartClass::end()
{
    // wait for transmission of outgoing data
    flush();

    // Disable receiver and transmitter as well as the RX complete and
    // data register empty interrupts.
    // clear any received data
    _rx_buffer_head = _rx_buffer_tail;

    _written = false;
}

int UartClass::available(void)
{
    return mockstream.available();
    // return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int UartClass::peek(void)
{
  /*  if (_rx_buffer_head == _rx_buffer_tail) {
        return -1;
    } else {
        return _rx_buffer[_rx_buffer_tail];
    }*/
   return mockstream.peek();
}

int UartClass::read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    /*if (_rx_buffer_head == _rx_buffer_tail) {
        return -1;
    } else {
        unsigned char c = _rx_buffer[_rx_buffer_tail];
        _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return c;
    }*/
    return mockstream.read();
}

int UartClass::availableForWrite(void)
{
    /*tx_buffer_index_t head;
    tx_buffer_index_t tail;

    TX_BUFFER_ATOMIC {
        head = _tx_buffer_head;
        tail = _tx_buffer_tail;
    }
    if (head >= tail) return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
    return tail - head - 1;*/
    return 0;
}

void UartClass::flush()
{
    // If we have never written a byte, no need to flush. This special
    // case is needed since there is no way to force the TXCIF (transmit
    // complete) bit to 1 during initialization
    if (!_written) {
        return;
    }
    

    

   
}

size_t UartClass::write(uint8_t c)
{
    _written = true;

    // If the buffer and the data register is empty, just write the byte
    // to the data register and be done. This shortcut helps
    // significantly improve the effective data rate at high (>
    // 500kbit/s) bit rates, where interrupt overhead becomes a slowdown.
   
    
    

    //Check if we are inside an ISR already (could be from by a source other than UART),
    // in which case the UART ISRs will be blocked.
    mockstream.write(c);

    return 1;
}
