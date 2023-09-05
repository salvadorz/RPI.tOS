/**
 * @file irq_reg_bcm2711.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Interrupt Register Map for bcm2711
 *
 */

#ifndef IRQ_REG_BCM2711_H_
#define IRQ_REG_BCM2711_H_

// Includes
#include "common.h"

#include "base_addr.h"

#define IRQ_STS_REG_OFFSET (0x0000B230) /* IRQ Register MAP table for IRQ Status*/

#define IRQ0_REG_OFFSET    (0x0000B200) /* IRQ Register MAP table for Core 0*/
#define IRQ1_REG_OFFSET    (0x0000B240) /* IRQ Register MAP table for Core 1*/
#define IRQ2_REG_OFFSET    (0x0000B280) /* IRQ Register MAP table for Core 2*/
#define IRQ3_REG_OFFSET    (0x0000B2c0) /* IRQ Register MAP table for Core 3*/

struct IRQ_REG {
  reg32 IRQx_PENDING_0; /* ARM Core 'x' IRQ Enabled Int Pending bits [31:0]*/
  reg32 IRQx_PENDING_1; /* ARM Core 'x' IRQ Enabled Int Pending bits [63:32]*/
  reg32 IRQx_PENDING_2; /* ARM Core 'x' IRQ Enabled Int Pending bits [79:64]*/
  reg32 const RSRVD0;
  reg32 IRQx_SET_EN_0; /* Write to Set ARM Core 'x' IRQ enable bits [31:0]*/
  reg32 IRQx_SET_EN_1; /* Write to Set ARM Core 'x' IRQ enable bits [63:32]*/
  reg32 IRQx_SET_EN_2; /* Write to Set ARM Core 'x' IRQ enable bits [79:64]*/
  reg32 const RSRVD1;
  reg32 IRQx_CLR_EN_0; /* Write to Clear ARM Core 'x' IRQ enable bits [31:0]*/
  reg32 IRQx_CLR_EN_1; /* Write to Clear ARM Core 'x' IRQ enable bits [63:32]*/
  reg32 IRQx_CLR_EN_2; /* Write to Clear ARM Core 'x' IRQ enable bits [79:64]*/
};

struct IRQ_STS {
  reg32 IRQ_STATUS0; /* Interrupt Line Bits [31:0]*/
  reg32 IRQ_STATUS1; /* Interrupt Line Bits [63:32]*/
  reg32 IRQ_STATUS2; /* Interrupt Line Bits [79:64]*/
};

#define IRQ_STS_REG_MAP ((struct IRQ_STS *)(PBASE + IRQ0_REG_OFFSET))

#define IRQ0_REG_MAP ((struct IRQ_REG *)(PBASE + IRQ0_REG_OFFSET))
#define IRQ1_REG_MAP ((struct IRQ_REG *)(PBASE + IRQ1_REG_OFFSET))
#define IRQ2_REG_MAP ((struct IRQ_REG *)(PBASE + IRQ2_REG_OFFSET))
#define IRQ3_REG_MAP ((struct IRQ_REG *)(PBASE + IRQ3_REG_OFFSET))

#endif /* IRQ_REG_BCM2711_H_ */