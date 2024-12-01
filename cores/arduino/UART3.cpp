
#include "Arduino.h"
#include "UART.h"

#if SERIAL_HOWMANY > 3
 USART_t HWSERIAL_struct3;


 uint8_t PIN_WIRE_HWSERIAL3_RX=2;
 uint8_t PIN_WIRE_HWSERIAL3_TX =3;
 uint8_t HWSERIAL3_DRE_VECTOR_NUM=4;
 uint8_t HWSERIAL3_MUX=5;
UartClass _UART3_(& HWSERIAL_struct3,PIN_WIRE_HWSERIAL3_RX , PIN_WIRE_HWSERIAL3_TX, HWSERIAL3_DRE_VECTOR_NUM, HWSERIAL3_MUX);
//UartClass Serial;

//UartClass(volatile USART_t *hwserial_module, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t dre_vect_num, uint8_t uart_mux);

#endif