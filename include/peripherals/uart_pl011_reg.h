/**
 * @file uart_pl011_reg.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for UART PL011 registers map
 *
 */

#ifndef UART_PL011_REG_H_
#define UART_PL011_REG_H_

// Includes
#include "common.h"

#include "base_addr.h"

#define UART_DATA_MSK  (0xFF) // Data Field Mask Register
#define UART_TXFF_BIT  (5U)   // Transmit FIFO full
#define UART_RXFE_BIT  (4U)   // Receive FIFO empty
#define UART_CRTX_BIT  (8U)   // Transmit Enable Control Register
#define UART_CRRX_BIT  (9U)   // Receive Enable Control Register
#define UART_LCRH_FEN  (4U)   // Enable FIFOs if SET (FIFO Mode)
#define UART_8BIT_WRD  (3U)   // World Length 8 data bits
#define UART_7BIT_WRD  (2U)   // World Length 7 data bits
#define UART_6BIT_WRD  (1U)   // World Length 6 data bits
#define UART_5BIT_WRD  (0U)   // World Length 6 data bits
#define UART_WORD_LEN  (5U)   // World Length bits transmitted bit pox


#define UART_TX_READY  (1 << UART_TXFF_BIT) // Transmitter IReady
#define UART_RX_READY  (1 << UART_RXFE_BIT) // Data Ready
#define UART_TX_ENABLE (1 << UART_CRTX_BIT)
#define UART_RX_ENABLE (1 << UART_CRRX_BIT)
#define UART_CNTRL_CFG (UART_TX_ENABLE | UART_RX_ENABLE)

#define MHz                (1000000)
#define UART_CLK           (48 * MHz)

// BAUD_DIV = (UARTCLK / (16 * baud_rate)) = 26.0416666667
// FRAC_DIV = ((BAUD_DIV % 1 ) * 64) = (0.0416666667 * 64) + 0.5)  = 3
#define BAUD_IRATE_115200  (26)
#define BAUD_FRATE_115200  (3)

#define UART0_REG_OFFSET   (0x00201000)
#define UART2_REG_OFFSET   (0x00201400) /* Only in RPI_4 */
#define UART3_REG_OFFSET   (0x00201600) /* Only in RPI_4 */
#define UART4_REG_OFFSET   (0x00201800) /* Only in RPI_4 */
#define UART5_REG_OFFSET   (0x00201a00) /* Only in RPI_4 */

struct UART_PL011 {
  reg32 UART_DR;   /* Data Register*/
  reg32 RSRECR;    /* Receive status/error register*/
  reg32 const RESERVED0[4];
  reg32 UART_FR;   /* Flag Register */
  reg32 const RESERVED1;
  reg32 UART_ILPR; /* Not in use */
  reg32 UART_IBRD; /* Integer Baud Rate Divisor */
  reg32 UART_FBRD; /* Fractional Baud Rate Divisor */
  reg32 UART_LCRH; /* Line Control register */
  reg32 UART_CR;   /* Control register */
  reg32 UART_IFLS; /* Interrupt FIFO Level Select Register */
  reg32 UART_IMSC; /* Interrupt Mask Set Clear Register */
};

#define UART0_REG_MAP ((struct UART_PL011 *)(PBASE + UART0_REG_OFFSET))
#define UART2_REG_MAP ((struct UART_PL011 *)(PBASE + UART2_REG_OFFSET))
#define UART3_REG_MAP ((struct UART_PL011 *)(PBASE + UART3_REG_OFFSET))
#define UART4_REG_MAP ((struct UART_PL011 *)(PBASE + UART4_REG_OFFSET))
#define UART5_REG_MAP ((struct UART_PL011 *)(PBASE + UART5_REG_OFFSET))

#endif /* UART_PL011_REG_H_ */