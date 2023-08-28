/**
 * @file common.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for common files
 *
 */

#ifndef COMMON_H_
#define COMMON_H_

// Include
#include <stdint.h>

#define SET (1U)
#define CLR (0U)

#define BYTE_MSK (0xFFU)

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile u32 reg32;

#endif /* COMMON_H_ */