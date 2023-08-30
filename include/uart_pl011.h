/**
 * @file uart_pl011.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for uart_pl011
 *
 */

#ifndef UART_PL011_H_
#define UART_PL011_H_

// Includes
#include "gpio.h"
#include "peripherals/uart_pl011_reg.h"

#define TXD0 GPIO14 /* Options GPIO32 GPIO36 */
#define RXD0 GPIO15 /* Options GPIO33 GPIO37 */

#if ((GPIO_GET_PIN_NUM(TXD0) == GPIO_GET_PIN_NUM(GPIO14)) && \
     (GPIO_GET_PIN_CFG(TXD0) != GPIO_FSEL_ALT0))
  #pragma message "Check PIN GPIO14 is not in use"
#endif
#if ((GPIO_GET_PIN_NUM(RXD0) == GPIO_GET_PIN_NUM(GPIO15)) && \
     (GPIO_GET_PIN_CFG(RXD0) != GPIO_FSEL_ALT0))
  #pragma message "Check PIN GPIO15 is not in use"
#endif

void uart_pl011_init();
char uart_pl011_recv();
void uart_pl011_send(char c);
void uart_pl011_send_string(char *str);

#endif /* UART_PL011_H_ */