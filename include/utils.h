/**
 * @file utils.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for utils
 *
 */

#ifndef UTILS_H_
#define UTILS_H_

// Includes
#include "common.h"

#define DO_PRAGMA(x) _Pragma(#x)
#if 0
  #define TODO(x) DO_PRAGMA(message("TODO - " #x))
#else
  #define TODO(x) // TODO(x)
#endif

/**
 * @brief Clears or Writes a field (msk/val) in register at start bit (pox)
 */
#define CLR_FLD_REG(reg, msk, pox) (reg & ~(msk << pox))
#define SET_FLD_REG(reg, val, pox) (reg | (val << pox))
#define CLR_BIT_POX(pox)           ~(1 << (pox))
#define SET_BIT_POX(pox)           (1 << (pox))

/**
 * @brief wait for n-ticks (cycles) amount
 *
 * @param ticks
 */
void delay_ticks(u64 ticks);
/**
 * @brief Inserts value into address
 *
 * @param address
 * @param value
 */
void write_reg(u64 address, u32 value);
/**
 * @brief Get value of address
 *
 * @param address
 * @return u32
 */
u32 read_reg(u64 address);
/**
 * @brief Get the processor id
 * 
 * @return u32 
 */
u32 get_proc_id();
/**
 * @brief Get Exception Level (0-3)
 * 0 - Usr; 1 - OS; 2 - Hypervisor; 3 - FW (secure)
 * @return u32
 */
u32 get_exc_lvl();

#endif /* UTILS_H_ */