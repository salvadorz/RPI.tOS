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
#include "utils.h"
#include "mini_uart.h"
#include "peripherals/aux_reg.h"

void mini_uart_init() {
  gpio_pin_set_func(GPIO_GET_PIN_NUM(TXD1), GPIO_GET_PIN_CFG(TXD1));
  gpio_pin_set_func(GPIO_GET_PIN_NUM(RXD1), GPIO_GET_PIN_CFG(RXD1));

  gpio_pin_enable(GPIO_GET_PIN_NUM(TXD1));
  gpio_pin_enable(GPIO_GET_PIN_NUM(RXD1));

  // AUXENB :MiniUart Enable
  AUX_REG_MAP->AUX_ENABLES = SET_BIT_POX(0);
  // Disable receive and transmit interrupts
  AUX_REG_MAP->AUX_MU_IER = CLR;
  // Enable 8 bit mode
  AUX_REG_MAP->AUX_MU_LCR  = SET_FLD_REG(AUX_REG_MAP->AUX_MU_LCR, mUART_8BIT_MODE, 0);
  // UART1_RTS line is high
  AUX_REG_MAP->AUX_MU_MCR  = CLR;
  // Set the Baud Rate
  AUX_REG_MAP->AUX_MU_BAUD = BAUD_RATE_REG_16B;
  // UART TX and RX Enable (Enabled by default after reset)
  AUX_REG_MAP->AUX_MU_CNTL = SET_FLD_REG(AUX_REG_MAP->AUX_MU_CNTL, mUART_CNTRL_CFG, 0);

  // Starting from known pox
  mini_uart_send('\r');
  mini_uart_send('\n');
}

void mini_uart_send(char c) {
  // @TODO Change blocking method: Polling
  while (!(AUX_REG_MAP->AUX_MU_LSR & mUART_TX_READY));

  // Transmit data
  AUX_REG_MAP->AUX_MU_IO = c;

}

char mini_uart_recv() {
  // @TODO Change blocking method: Polling
  while (!(AUX_REG_MAP->AUX_MU_LSR & mUART_RX_READY));

  // Receive data
  return AUX_REG_MAP->AUX_MU_IO & BYTE_MSK;
}

void mini_uart_send_string(char *str) {
  while (*str) {
    if ('\n' == *str) {
      // add a cariage return first
      mini_uart_send('\r');
    }
    mini_uart_send(*str);
    ++str;
  }
}

#endif /* MINI_UART_C_ */