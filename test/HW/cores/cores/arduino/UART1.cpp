
#include "Arduino.h"
#include "UART.h"

#if SERIAL_HOWMANY > 1
 USART_t HWSERIAL_struct1;


 uint8_t PIN_WIRE_HWSERIAL1_RX=2;
 uint8_t PIN_WIRE_HWSERIAL1_TX =3;
 uint8_t HWSERIAL1_DRE_VECTOR_NUM=4;
 uint8_t HWSERIAL1_MUX=5;
UartClass _UART1_(& HWSERIAL_struct1,PIN_WIRE_HWSERIAL1_RX , PIN_WIRE_HWSERIAL1_TX, HWSERIAL1_DRE_VECTOR_NUM, HWSERIAL1_MUX);
//UartClass Serial;

//UartClass(volatile USART_t *hwserial_module, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t dre_vect_num, uint8_t uart_mux);

#endif