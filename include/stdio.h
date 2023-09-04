 /**
 * @file stdio.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for stdio
 *
 */

#ifndef STDIO_H_
#define STDIO_H_

/* configure the underlaying output char method*/
#define output_char(x)   mini_uart_send(x)
#define STDIO_PERIPHERAL "mini_uart.h"

 // Includes
#include "printf.h"
#include STDIO_PERIPHERAL

 /**
  * @brief Underliying method for printf
  * 
  * @param p 
  * @param c 
  */
void putc(void *p, char c);

#endif /* STDIO_H_ */