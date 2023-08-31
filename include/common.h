/**
 * @file common.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for common files
 *
 */

#ifndef COMMON_H_
#define COMMON_H_


#ifndef TRUE
  #define TRUE  (1U)
  #define FALSE (0U)
#endif

#ifndef ENABLE
  #define ENABLE  (1U)
  #define DISABLE (0U)
#endif

#define SET (1U)
#define CLR (0U)

#define BYTE_MSK (0xFFU)

typedef unsigned char     u8;
typedef unsigned short    u16;
typedef unsigned int      u32;
typedef unsigned long int u64;

typedef signed char       s8;
typedef signed short      s16;
typedef signed int        s32;
typedef signed long int   s64;

typedef volatile u32 reg32;

#endif /* COMMON_H_ */