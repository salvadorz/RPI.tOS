/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of RPI tOS                                                *
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
 * @file uart_pl011.c
 * @author Salvador Z
 * @date 30 Aug 2023
 * @brief File for uart_pl011
 *
 */

#include "uart_pl011.h"
#include "utils.h"

void uart_pl011_init() {
  // Cfg GPIOs for TXD and RXD
  gpio_pin_set_func(GPIO_GET_PIN_NUM(TXD0), GPIO_GET_PIN_CFG(TXD0));
  gpio_pin_set_func(GPIO_GET_PIN_NUM(RXD0), GPIO_GET_PIN_CFG(RXD0));

  gpio_pin_enable(GPIO_GET_PIN_NUM(TXD0));
  gpio_pin_enable(GPIO_GET_PIN_NUM(RXD0));

  // Disable UART while is Initialized
  UART0_REG_MAP->UART_CR = CLR;
  // Integer Baud Rate divisor
  UART0_REG_MAP->UART_IBRD = BAUD_IRATE_115200;
  // Fractional Baud Rate Divisor
  UART0_REG_MAP->UART_FBRD = BAUD_FRATE_115200;
  // Enable 8 bit mode
  UART0_REG_MAP->UART_LCRH = SET_FLD_REG(UART0_REG_MAP->UART_LCRH, UART_8BIT_WRD, UART_WORD_LEN);
  // Enable FIFOs
  UART0_REG_MAP->UART_LCRH |= SET_BIT_POX(UART_LCRH_FEN);
  // UART0 Mask Interrupts
  UART0_REG_MAP->UART_IMSC = CLR;

  // UART TX and RX Enable (Enabled by default after reset)
  UART0_REG_MAP->UART_CR = SET_FLD_REG(UART0_REG_MAP->UART_CR, UART_CNTRL_CFG, 0);

  // Starting from known pox
  uart_pl011_send('\r');
  uart_pl011_send('\n');
}

char uart_pl011_recv() {
  // @TODO Change blocking method: Polling
  while ((UART0_REG_MAP->UART_FR & UART_RX_READY));

  // Receive data
  return UART0_REG_MAP->UART_DR & UART_DATA_MSK;
}

void uart_pl011_send(char c) {
  // @TODO Change blocking method: Polling
  while ((UART0_REG_MAP->UART_FR & UART_TX_READY));

  // Transmit data
  UART0_REG_MAP->UART_DR = c;
}

void uart_pl011_send_string(char *str) {
  while (*str) {
    if ('\n' == *str) {
      // add a cariage return first
      uart_pl011_send('\r');
    }
    uart_pl011_send(*str);
    ++str;
  }
}