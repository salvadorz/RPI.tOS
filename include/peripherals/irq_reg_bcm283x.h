/**
 * @file irq_reg_bcm283x.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Interrupt Register Map for bcm283x
 *
 */

#ifndef IRQ_REG_BCM283X_H_
#define IRQ_REG_BCM283X_H_

// Includes
#include "common.h"

#include "base_addr.h"

#define IRQ_REG_OFFSET (0x0000B200)

struct IRQ_REG {
  reg32 IRQ_BASIC_PENDING;
  reg32 IRQ_PENDING_1; /* GPU pending reg [31:0] */
  reg32 IRQ_PENDING_2; /* GPU pending reg [63:32]*/
  reg32 IRQ_FIQ_CONTROL;
  reg32 IRQ_ENABLE_IRQS_1;
  reg32 IRQ_ENABLE_IRQS_2;
  reg32 IRQ_ENABLE_BASICS;
  reg32 IRQ_DISABLE_IRQS_1;
  reg32 IRQ_DISABLE_IRQS_2;
  reg32 IRQ_DISABLE_BASICS;
};

#define IRQ_REG_MAP ((struct IRQ_REG *)(PBASE + IRQ_REG_OFFSET))

#endif /* IRQ_REG_BCM283X_H_ */