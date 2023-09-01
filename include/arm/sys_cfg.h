/**
 * @file sys_cfg.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for System Control and Configuration
 *
 */

#ifndef SYS_CFG_H_
#define SYS_CFG_H_

// Includes
#include "common.h"

/***** /
 * AArch64 Exception Level and selected Stack Pointer
 *****/
#define EL0t (0)
#define EL1t (4)
#define EL1h (5)
#define EL2t (8)
#define EL2h (9)
#define EL3t (12)
#define EL3h (13)
//****/

#define RSRVD1    (ENABLED) // When XXXX is not Implemented
#define RSRVD0    (DISABLE) // When XXXX is not Implemented

#define L_ENDIAN  (ENABLED) // Data acces are Liitle Endian if Disable then Big Endian
#define I_CACHE   (DISABLE) // Instructions are Non/ Cacheable
#define D_CACHE   (DISABLE) // Cacheability control, for data accesses.
#define MMU_CFG   (DISABLE) // MMU (dis/en)able for EL1&0 stage 1 address translation.
#define AARCH64   (ENABLED) // The Execution state for EL1 is AArch64
#define SECURE_ST (ENABLED) // If Enable EL2-0 are in Non-Secure State. Disable indicates EL0-EL1 are in Secure State
#define IRQ_MASK  (ENABLED) // Interrupt Mask. Set to the value of PSTATE.x bit on taking the exception to EL3
#define SPSR_M_SP (EL1h)    // Exception Level and Stack Pointer Selected

#if L_ENDIAN
  #define EE_CFG (0)
#else
  #define EE_CFG (1)
#endif

// ***************************************
// SCTLR_EL1, System Control Register (EL1), Pg. 1487 Arch Registers / Pg. 6972 of AArch64-Reference-Manual.
// Provides top level control of the system, including its memory system, at EL1 and EL0.
// ***************************************

#define SCTLR_LSMAOE   (RSRVD1 << 29) // Load Multiple and Store Multiple Atomicity and Ordering Enable.
#define SCTLR_nTLSMD   (RSRVD1 << 28) // No Trap Load Multiple and Store Multiple to Device-nGRE/nGnRE/nGnRnE mem

#define SCTLR_EE_CFG   (EE_CFG << 25)
#define SCTLR_EOE_CFG  (EE_CFG << 24)

#define SCTLR_SPAN_CFG (RSRVD1 << 23)  // Set Privileged Access Never on taking an exception to EL1
#define SCTLR_EIS_CFG  (RSRVD1 << 22)  // Exception Entry is Context Sync
#define SCTLR_TSCXT    (RSRVD1 << 20)  // Trap EL0 Access to SCXTNUM_EL0 register
#define SCTLR_EOS_CFG  (RSRVD1 << 11)  // Exception Exit is Context Synchronizing.
#define SCTLR_I_CACHE  (I_CACHE << 12) // Stage 1 instruction access Cacheability control, for accesses at EL0 and EL1
#define SCTLR_D_CACHE  (D_CACHE << 2)
#define SCTLR_MMU_CFG  (MMU_CFG << 0)

#define SCTLR_EL1_REG_CFG                                                                        \
  (SCTLR_LSMAOE | SCTLR_nTLSMD | SCTLR_EE_CFG | SCTLR_EOE_CFG | SCTLR_SPAN_CFG | SCTLR_EIS_CFG | \
    SCTLR_TSCXT | SCTLR_EOS_CFG | SCTLR_I_CACHE | SCTLR_D_CACHE | SCTLR_MMU_CFG)

// ***************************************
// HCR_EL2, Hypervisor Configuration Register (EL2), Pg. 703 Arch Registers / Pg 6617 of AArch64-Reference-Manual.
// Provides configuration controls for virtualization, including defining
// whether various operations are trapped to EL2.
// ***************************************

#define HCR_RW_CFG       (AARCH64 << 31)
#define HCR_EL2_REG_CFG  (HCR_RW_CFG)

// ***************************************
// SCR_EL3, Secure Configuration Register (EL3), Pg. 1472 Arch Registers / Pg 6947 of AArch64-Reference-Manual.
// Defines the configuration of the current Security state
// ***************************************

#define SCR_RESERVED     (RSRVD1 << 5 | RSRVD1 << 4)
#define SCR_RW_CFG       (AARCH64 << 10) // The next lower level is AArch64 AArch32 Otherwise
#define SCR_NS_CFG       (SECURE_ST<< 0) // If Non-Secure State, mem access cannot access Secure Memory
#define SCR_EL3_REG_CFG  (SCR_RESERVED | SCR_RW_CFG | SCR_NS_CFG)

// ***************************************
// SPSR_EL3, Saved Program Status Register (EL3) Pg. 1606 Arch Registers / Pg. 819 of AArch64-Reference-Manual.
// Holds the saved process state when an exception is taken to EL3.
// ***************************************
#if (AARCH64)
  #define SPSR_ASE      (IRQ_MASK << 8)
  #define SPSR_IRQ      (IRQ_MASK << 7)
  #define SPSR_FIQ      (IRQ_MASK << 6)
  #define SPSR_MASK_ALL (SPSR_ASE | SPSR_IRQ | SPSR_FIQ)
  #define SPSR_M_SP_CFG (SPSR_M_SP<< 0)
  #define SPSR_REG_CFG  (SPSR_MASK_ALL | SPSR_M_SP_CFG)

#else
// TODO(Implement Behaviour for AARCH32 State(Mode))
#error Needs Config
#endif
#endif /* SYS_CFG_H_ */