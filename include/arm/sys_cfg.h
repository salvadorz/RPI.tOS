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
 * AArch64 Exception Level and selected Stack Pointer (t):thread or (h):hypervisor
 *****/
#define M_EL0t    (0)   /* Exception level M[3:2] (0 << 2) | M[0]0 (t)*/
#define M_EL1t    (4)   /* Exception level M[3:2] (1 << 2) | M[0]0 (t)*/
#define M_EL1h    (5)   /* Exception level M[3:2] (1 << 2) | M[0]1 (h)*/
#define M_EL2t    (8)   /* Exception level M[3:2] (2 << 2) | M[0]0 (t)*/
#define M_EL2h    (9)   /* Exception level M[3:2] (2 << 2) | M[0]1 (h)*/
#define M_EL3t    (12)  /* Exception level M[3:2] (3 << 2) | M[0]0 (t)*/
#define M_EL3h    (13)  /* Exception level M[3:2] (3 << 2) | M[0]1 (h)*/
//****/

/***** /
 * AArch64 Floating point Cfg
 *****/
#define FP_NO_TRAP_EL3 (0)  /* Execution of these instructions at EL1 and EL0 to be trapped*/
#define FP_NO_TRAP_EL1 (1)  /* Execution of these instructions at EL0 to be trapped*/
#define FP_NO_TRAP_EL0 (3)  /* Does not cause execution of any instructions to be trapped*/
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
#define SPSR_EL1  (M_EL1h)  // Exception Level and Stack Pointer Selected
#define SPSR_EL2  (M_EL2h)  // Exception Level and Stack Pointer Selected

#if L_ENDIAN
  #define EE_CFG (0)
#else
  #define EE_CFG (1)
#endif

// ***************************************
// SCTLR_EL1, System Control Register (EL1), Pg. 1487 Arch Registers / Pg. 6972 of AArch64-Reference-Manual.
// Provides top level control of the system, including its memory system, at EL1 and EL0.
// ***************************************

#define SCTLR_LSMAOE_EL1   (RSRVD1 << 29) // Load Multiple and Store Multiple Atomicity and Ordering Enable.
#define SCTLR_nTLSMD_EL1   (RSRVD1 << 28) // No Trap Load Multiple and Store Multiple to Device-nGRE/nGnRE/nGnRnE mem

#define SCTLR_EE_CFG_EL1   (EE_CFG << 25)
#define SCTLR_EOE_CFG_EL1  (EE_CFG << 24)

#define SCTLR_SPAN_CFG_EL1 (RSRVD1 << 23)  // Set Privileged Access Never on taking an exception to EL1
#define SCTLR_EIS_CFG_EL1  (RSRVD1 << 22)  // Exception Entry is Context Sync
#define SCTLR_TSCXT_EL1    (RSRVD1 << 20)  // Trap EL0 Access to SCXTNUM_EL0 register
#define SCTLR_EOS_CFG_EL1  (RSRVD1 << 11)  // Exception Exit is Context Synchronizing.
#define SCTLR_I_CACHE_EL1  (I_CACHE<< 12)  // Stage 1 instruction access Cacheability control, for accesses at EL0 and EL1
#define SCTLR_D_CACHE_EL1  (D_CACHE<<  2)
#define SCTLR_MMU_CFG_EL1  (MMU_CFG<<  0)

#define SCTLR_EL1_REG_CFG                                                                                              \
  (SCTLR_LSMAOE_EL1 | SCTLR_nTLSMD_EL1 | SCTLR_EE_CFG_EL1 | SCTLR_EOE_CFG_EL1 | SCTLR_SPAN_CFG_EL1 | SCTLR_EIS_CFG_EL1 \
  | SCTLR_TSCXT_EL1 | SCTLR_EOS_CFG_EL1 | SCTLR_I_CACHE_EL1 | SCTLR_D_CACHE_EL1 | SCTLR_MMU_CFG_EL1)

// ***************************************
// SCTLR_EL2, System Control Register (EL2), Pg. 1512 Arch Registers / Pg. 6972 of AArch64-Reference-Manual.
// Provides top level control of the system, including its memory system, at EL1 and EL0.
// ***************************************

#define SCTLR_LSMAOE_EL2   (RSRVD1 << 29) // Load Multiple and Store Multiple Atomicity and Ordering Enable.
#define SCTLR_nTLSMD_EL2   (RSRVD1 << 28) // No Trap Load Multiple and Store Multiple to Device-nGRE/nGnRE/nGnRnE mem

#define SCTLR_EE_CFG_EL2   (EE_CFG << 25)
#define SCTLR_EOE_CFG_EL2  (EE_CFG << 24)

#define SCTLR_SPAN_CFG_EL2 (RSRVD1 << 23)  // Set Privileged Access Never on taking an exception to EL1
#define SCTLR_EIS_CFG_EL2  (RSRVD1 << 22)  // Exception Entry is Context Sync
#define SCTLR_TSCXT_EL2    (RSRVD0 << 20)  // Trap EL0 Access to SCXTNUM_EL0 register
#define SCTLR_TWE_CFG_EL2  (RSRVD1 << 18)  // Traps execution of WFE instructions at EL0 to EL2, from both EXPCN states.
#define SCTLR_TWI_CFG_EL2  (RSRVD1 << 16)  // Traps execution of WFI instructions at EL0 to EL2, from both EXPCN states.
#define SCTLR_EOS_CFG_EL2  (RSRVD1 << 11)  // Exception Exit is Context Synchronizing.
#define SCTLR_I_CACHE_EL2  (I_CACHE<< 12)  // Stage 1 instruction access Cacheability ctrl, for accesses at EL0 and EL1
#define SCTLR_D_CACHE_EL2  (D_CACHE<<  2)
#define SCTLR_MMU_CFG_EL2  (MMU_CFG<<  0)

#define SCTLR_EL2_RSRVD1                                                                                               \
  (SCTLR_LSMAOE_EL2 | SCTLR_nTLSMD_EL2 | SCTLR_SPAN_CFG_EL2 | SCTLR_EIS_CFG_EL2 | SCTLR_TWE_CFG_EL2 | SCTLR_TWI_CFG_EL2)
#define SCTLR_EL2_REG_CFG                                                                            \
  (SCTLR_EL2_RSRVD1 | SCTLR_EE_CFG_EL2 | SCTLR_EOE_CFG_EL2 | SCTLR_EOS_CFG_EL2 | SCTLR_I_CACHE_EL2 | \
   SCTLR_D_CACHE_EL2 | SCTLR_MMU_CFG_EL2)

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
#define SCR_RW_CFG       (AARCH64 << 10) // The next lower level is AArch64, AArch32 Otherwise
#define SCR_NS_CFG       (SECURE_ST<< 0) // If Non-Secure State, mem access cannot access Secure Memory
#define SCR_EL3_REG_CFG  (SCR_RESERVED | SCR_RW_CFG | SCR_NS_CFG)

// ***************************************
// CPACR_EL1, Architectural Feature Access Control Register (EL3) Pg. 296 Arch Registers / Pg. 6407 of AArch64-Ref M.
// Controls access to trace, SVE, and Advanced SIMD and floating-point functionality.
// ***************************************
#define CPACR_FP_EN     (FP_NO_TRAP_EL0 << 20)
#define CPACR_REG_CFG   (CPACR_FP_EN)

// ***************************************
// SPSR_EL3, Saved Program Status Register (EL3) Pg. 1606 Arch Registers / Pg. 819 of AArch64-Reference-Manual.
// Holds the saved process state when an exception is taken to EL3.
// ***************************************
#if (AARCH64)
  #define SPSR_ASE      (IRQ_MASK << 8)
  #define SPSR_IRQ      (IRQ_MASK << 7)
  #define SPSR_FIQ      (IRQ_MASK << 6)
  #define SPSR_MASK_ALL (SPSR_ASE | SPSR_IRQ | SPSR_FIQ)
  #define SPSR_M_SP_EL1 (SPSR_EL1 << 0)
  #define SPSR_M_SP_EL2 (SPSR_EL2 << 0)
  #define SPSR_REG_EL1  (SPSR_MASK_ALL | SPSR_M_SP_EL1)
  #define SPSR_REG_EL2  (SPSR_MASK_ALL | SPSR_M_SP_EL2)

#else
// TODO(Implement Behaviour for AARCH32 State(Mode))
#error Needs Config
#endif
#endif /* SYS_CFG_H_ */