/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of RPitOS                                                 *
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
 * @file kernel.c
 * @author Salvador Z
 * @date 27 Aug 2023
 * @brief File for kernel
 *
 */

#include "common.h"
#include "mini_uart.h"
#include "stdio.h"
#include "rpi_cfg.h"
#include "utils.h" // get_proc_id


void kernel_init() {
  // uart_pl011_init();
  mini_uart_init();
  init_printf(0, putc);
  // System is in Hypervisor Exception level
  printf("Rasperry PI %d Bare Metal OS Initializing...\n", RPI_VERSION);
}

int kernel_main() {

  while (1) {
    // echo
    printf("%c",mini_uart_recv());
  }

  return 0;
}

#if MULTICORE

static u32 sem = 0;

int kernel_multi_main() {

  u32 const proc_id = get_proc_id();

  // Wait for prev Core to print
  while(proc_id != sem){;}

  printf("Core %d running...\n", proc_id);
  ++sem;

  if (CORE0 == proc_id) {
    while (CORE_MAX != sem) {;}

    while (1) {
      // echo
      printf("%c", mini_uart_recv());
    }
  }

  return 0;
}
#endif