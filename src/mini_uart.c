/**
 * @file mini_uart.c
 * @author Salvador Z
 * @version 1.0
 * @brief File for mini UART
 *
 */

#ifndef MINI_UART_C_
#define MINI_UART_C_

// Includes
#include "gpio.h"
#include "utils.h"
#include "mini_uart.h"
#include "peripherals/aux_reg.h"

void uart_init() {
  gpio_pin_set_func(GPIO_GET_PIN_NUM(TXD1), GPIO_GET_PIN_CFG(TXD1));
  gpio_pin_set_func(GPIO_GET_PIN_NUM(RXD1), GPIO_GET_PIN_CFG(RXD1));

  gpio_pin_enable(GPIO_GET_PIN_NUM(TXD1));
  gpio_pin_enable(GPIO_GET_PIN_NUM(RXD1));

  // AUXENB :MiniUart Enable
  AUX_REG_MAP->AUX_ENABLES = SET_BIT_POX(0);
  AUX_REG_MAP->AUX_MU_IER  = CLR;
  AUX_REG_MAP->AUX_MU_LCR  = SET_FLD_REG(AUX_REG_MAP->AUX_MU_LCR, UART_8BIT_MODE, 0);
  // No RTS
  AUX_REG_MAP->AUX_MU_MCR  = CLR;

  AUX_REG_MAP->AUX_MU_BAUD = BAUD_RATE_REG_16B;
  AUX_REG_MAP->AUX_MU_CNTL = SET_FLD_REG(AUX_REG_MAP->AUX_MU_CNTL, UART_CNTRL_CFG, 0);

  // Starting from known pox
  uart_send('\r');
  uart_send('\n');
}

void uart_send(char c) {
  // @TODO Change blocking method: Polling
  while (!(AUX_REG_MAP->AUX_MU_LSR & UART_TX_READY));

  // Transmit data
  AUX_REG_MAP->AUX_MU_IO = c;

}

char uart_recv() {
  // @TODO Change blocking method: Polling
  while (!(AUX_REG_MAP->AUX_MU_LSR & UART_RX_READY));

  // Receive data
  return AUX_REG_MAP->AUX_MU_IO & BYTE_MSK;
}

void uart_send_string(char *str) {
  while (*str) {
    if ('\n' == *str) {
      // add a cariage return first
      uart_send('\r');
    }
    uart_send(*str);
    ++str;
  }
}

#endif /* MINI_UART_C_ */