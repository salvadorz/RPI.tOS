/**
 * @file mini_uart.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for mini_uart API
 *
 */

#ifndef MINI_UART_H_
#define MINI_UART_H_

// Includes
#include "gpio.h"

#define TXD1 GPIO14
#define RXD1 GPIO15

#define mUART_TX_READY  (20U) // Transmitter IDLE AUX_MU_LSR
#define mUART_RX_READY  (1U)  // Data Ready
#define mUART_8BIT_MODE (3U)
#define mUART_TX_flwCTS (8U) // Auto flow-ctrl using CTS
#define mUART_RX_as_RTR (4U) // Ready to Receive with RST line
#define mUART_TX_ENABLE (2U)
#define mUART_RX_ENABLE (1U)
#define mUART_CNTRL_CFG (mUART_TX_ENABLE | mUART_RX_ENABLE)

#define MHz               (1000000)
#define BAUD_RATE_9600    (9600)
#define BAUD_RATE_19200   (19200)
#define BAUD_RATE_57600   (57600)
#define BAUD_RATE_115200  (115200)
#define BAUD_RATE_DEFAULT BAUD_RATE_115200
#if (RPI_VERSION == 3)
  #define SYSTEM_CLOCK_FREQ (250 * MHz)
#elif (RPI_VERSION == 4)
  #define SYSTEM_CLOCK_FREQ (500 * MHz)
#endif
#define BAUD_RATE_REG_16B ((SYSTEM_CLOCK_FREQ / (BAUD_RATE_DEFAULT * 8)) - 1) & 0xFFFF;

void mini_uart_init();
char mini_uart_recv();
void mini_uart_send(char c);
void mini_uart_send_string(char *str);

#endif /* MINI_UART_H_ */