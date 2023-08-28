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

#define UART_TX_READY  (20U) // Transmitter IDLE AUX_MU_LSR
#define UART_RX_READY  (1U)  // Data Ready
#define UART_8BIT_MODE (3U)
#define UART_TX_flwCTS (8U) // Auto flow-ctrl using CTS
#define UART_RX_as_RTR (4U) //Ready to Receive with RST line
#define UART_TX_ENABLE (2U)
#define UART_RX_ENABLE (1U)
#define UART_CNTRL_CFG (UART_TX_ENABLE | UART_RX_ENABLE)

#if (RPI_VERSION == 3)
    #define UART_BAUD_RATE (270U) // 115200 @ 250Mhz
#elif (RPI_VERSION == 4)
    #define UART_BAUD_RATE (541U) // 115200 @ 500Mhz
#endif

void uart_init();
char uart_recv();
void uart_send(char c);
void uart_send_string(char *str);

#endif /* MINI_UART_H_ */