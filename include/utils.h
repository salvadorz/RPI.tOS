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

#endif /* UTILS_H_ */