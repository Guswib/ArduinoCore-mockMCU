#pragma once


// Pin count
// ----
#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif

#define PINS_COUNT           (PINCOUNT_fn())
#define NUM_DIGITAL_PINS     (20u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (1u)

/****** DAC CORE DEFINES *******/
#define DAC8_HOWMANY (0)
#define DAC12_HOWMANY (1)
#define DAC         A0
#define IS_DAC(x)   (x == DAC ? true : false)
#define DAC_ADDRESS_12_CH0          R_DAC_BASE

// LEDs
// ----
#define PIN_LED     (13u)
#define LED_BUILTIN PIN_LED
#define LED_TX      (21u)
#define LED_RX      (22u)

/****** RTC CORE DEFINES *******/
#define RTC_HOWMANY     1

/****** UART CORE DEFINES ******/

#define SERIAL_HOWMANY		1
#define UART1_TX_PIN        1
#define UART1_RX_PIN        0

/****** WIRE CORE DEFINES ******/

#define WIRE_HOWMANY      1
#define WIRE_SDA_PIN      18 /* A4 */
#define WIRE_SCL_PIN      19 /* A5 */

static const uint8_t SDA = WIRE_SDA_PIN;
static const uint8_t SCL = WIRE_SCL_PIN;

/****** SPI CORE DEFINES ******/

#define SPI_HOWMANY       1

#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)
#define PIN_SPI_CS    (10)
#define FORCE_SPI_MODE  (MODE_SPI)

/* EEPROM DEFINES */

#define ARDUINO_FLASH_TYPE  LP_FLASH
#define FLASH_BASE_ADDRESS  0x40100000
#define FLASH_TOTAL_SIZE    0x2000
#define FLASH_BLOCK_SIZE    0x400
