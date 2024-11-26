
#include "Arduino.h"
#include "UART.h"

#if SERIAL_HOWMANY > 3
volatile USART_t HWSERIAL_struct;


volatile uint8_t PIN_WIRE_HWSERIAL0_RX=2;
volatile uint8_t PIN_WIRE_HWSERIAL0_TX =3;
volatile uint8_t HWSERIAL0_DRE_VECTOR_NUM=4;
volatile uint8_t HWSERIAL0_MUX=5;
UartClass _UART3_(& HWSERIAL_struct,PIN_WIRE_HWSERIAL0_RX , PIN_WIRE_HWSERIAL0_TX, HWSERIAL0_DRE_VECTOR_NUM, HWSERIAL0_MUX);
//UartClass Serial;

//UartClass(volatile USART_t *hwserial_module, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t dre_vect_num, uint8_t uart_mux);

#endif