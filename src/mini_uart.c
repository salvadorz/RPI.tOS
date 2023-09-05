/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of RPitoS                                                 *
 *                                                                             *
 *   Permission is hereby granted, free of charge, to any person obtaining a   *
 *   copy of this software and associated documentation files (the Software)   *
 *   to deal in the Software without restriction including without limitation  *
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,  *
 *   and/or sell copies ot the Software, and to permit persons to whom the     *
 *   Software is furnished to do so, subject to the following conditions:      *
 *                                                                             *
 *   The above copyright notice and this permission notice shall be included   *
 *   in all copies or substantial portions of the Software.                    *
 *                                                                             *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   *
 *   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARANTIES OF MERCHANTABILITY *
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL   *
 *   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR      *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,     *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE        *
 *   OR OTHER DEALINGS IN THE SOFTWARE.                                        *
 ******************************************************************************/

/**
 * @file mini_uart.c
 * @author Salvador Z
 * @date 30 Aug 2023
 * @brief File for mini_uart impl
 *
 */

// Includes
#include "mini_uart.h"
#include "peripherals/aux_reg.h"
#include "utils.h"

void mini_uart_init() {
  gpio_pin_set_func(GPIO_GET_PIN_NUM(TXD1), GPIO_GET_PIN_CFG(TXD1));
  gpio_pin_set_func(GPIO_GET_PIN_NUM(RXD1), GPIO_GET_PIN_CFG(RXD1));

  gpio_pin_enable(GPIO_GET_PIN_NUM(TXD1));
  gpio_pin_enable(GPIO_GET_PIN_NUM(RXD1));

  // AUXENB :MiniUart Enable
  AUX_REG_MAP->AUX_ENABLES = SET_BIT_POX(0);
  // Enable receive and disable transmit interrupts
  AUX_REG_MAP->AUX_MU_IER = mUART_RX_IRQ_EN;
  // Enable 8 bit mode
  AUX_REG_MAP->AUX_MU_LCR = SET_FLD_REG(AUX_REG_MAP->AUX_MU_LCR, mUART_8BIT_MODE, 0);
  // UART1_RTS line is high
  AUX_REG_MAP->AUX_MU_MCR = CLR;
  // Set the Baud Rate
  AUX_REG_MAP->AUX_MU_BAUD = BAUD_RATE_REG_16B;
  // UART TX and RX Enable (Enabled by default after reset)
  AUX_REG_MAP->AUX_MU_CNTL = SET_FLD_REG(AUX_REG_MAP->AUX_MU_CNTL, mUART_CNTRL_CFG, 0);

  // Starting from known pox
  mini_uart_send('\r');
  mini_uart_send('\n');
}

void mini_uart_send(char c) {
  // TODO(Change blocking method: Polling)
  while (!(AUX_REG_MAP->AUX_MU_LSR & mUART_TX_READY));

  // Transmit data
  AUX_REG_MAP->AUX_MU_IO = c;
}

char mini_uart_recv() {
  // TODO(Change blocking method: Polling)
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

void mini_uart_irq_handler(void) {
  while (mUART_RX_IRQ_ST == (AUX_REG_MAP->AUX_MU_IIR & mUART_RX_IRQ_ST)) {
    mini_uart_send(mini_uart_recv());
    AUX_REG_MAP->AUX_MU_IIR |= mUART_RX_IRQ_ST; // Clear the fifo
  }
}