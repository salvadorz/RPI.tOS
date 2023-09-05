/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of RPI_tOS                                                *
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
 * @file irq.c
 * @author Salvador Z
 * @date 03 Sep 2023
 * @brief File for irq Impl
 */

#include "entry.h"
#include "irq.h"
#include "stdio.h"
#include "sys_timer.h"
#if (RPI_VERSION == 4)
  #include "peripherals/irq_reg_bcm2711.h"
#else
  #include "peripherals/irq_reg_bcm283x.h"
#endif

char const *entry_error_messages[] = {
  "SYNC_INVALID_EL1t",   "IRQ_INVALID_EL1t",   "FIQ_INVALID_EL1t",   "ERROR_INVALID_EL1T",

  "SYNC_INVALID_EL1h",   "IRQ_INVALID_EL1h",   "FIQ_INVALID_EL1h",   "ERROR_INVALID_EL1h",

  "SYNC_INVALID_EL0_64", "IRQ_INVALID_EL0_64", "FIQ_INVALID_EL0_64", "ERROR_INVALID_EL0_64",

  "SYNC_INVALID_EL0_32", "IRQ_INVALID_EL0_32", "FIQ_INVALID_EL0_32", "ERROR_INVALID_EL0_32"
};

void irq_interrupt_controller_enable(void) {
#if (RPI_VERSION == 4)
  IRQ0_REG_MAP->IRQx_SET_EN_0 = AUX_mUART_IRQ;
#else
  IRQ_REG_MAP->IRQ_ENABLE_IRQS_1 = AUX_mUART_IRQ;
#endif
}

void irq_invalid_entry_message(int type, unsigned long esr, unsigned long address) {
  printf("%s, ESR: %lx, address: %lx\n", entry_error_messages[type], esr, address);
}

void irq_handler(void) {
  u32 irq_lo = 0U;
//u32 irq_hi = 0U;
#if (RPI_VERSION == 4)
  irq_lo = IRQ0_REG_MAP->IRQx_PENDING_0;
//irq_hi = IRQ0_REG_MAP->IRQx_PENDING_1;
#else
  irq_lo = IRQ_REG_MAP->IRQ_PENDING_1;
//irq_hi = IRQ_REG_MAP->IRQ_PENDING_2;
#endif
  if (SYS_TIMER_IRQ_1 & irq_lo) {
    // Clear the IRQ bit
    irq_lo &= ~SYS_TIMER_IRQ_1;
    // TODO(Implement Sys Timer irq handler)
    // sys_timer_irq_handler();
  }
  if (AUX_mUART_IRQ & irq_lo) {
    // Clear the IRQ bit
    irq_lo &= ~AUX_mUART_IRQ;
    void mini_uart_irq_handler();
  }
  if (irq_lo) {
    printf("Unknown pending IRQ: %x\n", irq_lo);
  }
}