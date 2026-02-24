
#include "Arduino.h"
#include "UART.h"

#if SERIAL_HOWMANY > 2
 USART_t HWSERIAL_struct2;


 uint8_t PIN_WIRE_HWSERIAL2_RX=2;
 uint8_t PIN_WIRE_HWSERIAL2_TX =3;
 uint8_t HWSERIAL2_DRE_VECTOR_NUM=4;
 uint8_t HWSERIAL2_MUX=5;
UartClass _UART2_(& HWSERIAL_struct2,PIN_WIRE_HWSERIAL2_RX , PIN_WIRE_HWSERIAL2_TX, HWSERIAL2_DRE_VECTOR_NUM, HWSERIAL2_MUX);
//UartClass Serial;

//UartClass(volatile USART_t *hwserial_module, uint8_t hwserial_rx_pin, uint8_t hwserial_tx_pin, uint8_t dre_vect_num, uint8_t uart_mux);

#endif