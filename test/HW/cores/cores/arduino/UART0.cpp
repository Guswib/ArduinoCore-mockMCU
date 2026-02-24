
#include "Arduino.h"
#include "UART.h"

#if SERIAL_HOWMANY > 0
USART_t HWSERIAL_struct;


uint8_t PIN_WIRE_HWSERIAL0_RX=2;
uint8_t PIN_WIRE_HWSERIAL0_TX =3;
uint8_t HWSERIAL0_DRE_VECTOR_NUM=4;
uint8_t HWSERIAL0_MUX=5;
UartClass _UART0_(& HWSERIAL_struct,PIN_WIRE_HWSERIAL0_RX , PIN_WIRE_HWSERIAL0_TX, HWSERIAL0_DRE_VECTOR_NUM, HWSERIAL0_MUX);
//UartClass Serial;

//UartClass(volatile USART_t *hwserial_module, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t dre_vect_num, uint8_t uart_mux);

#endif
