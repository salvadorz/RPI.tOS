/**
 * @file gpio_reg.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for GPIO Register Map for BCM2711
 *
 */

#ifndef GPIO_REG_BCM2711_H_
#define GPIO_REG_BCM2711_H_

// Includes
#include "common.h"

#include "base_addr.h"

#define GPIO_FUNC_REG_MAX   (6U) /* GPFSEL0-5*/
#define GPIO_FSEL_BIT_MAX   (30U) /* FSEL BIT FIELD MAX n-PIN Cfg per Register*/
#define GPIO_FSEL_BIT_GRP   (3U)  /* 3 bits group for FSEL Cfg*/
#define GPIO_FSEL_BIT_MSK   ((1 << GPIO_FSEL_BIT_GRP) - 1) /* FSELn Bit field Mask*/
#define GPIO_PUPD_CTL_MAX   (4U)  /* GPIO_PUP_PDN_CNTRL_REG0-3 */
#define GPIO_PUPD_PIN_GRP   (16U) /* GPIO PUPPD MAX nPin per Register */
#define GPIO_REG_OFFSET     (0x00200000)

struct GPIO_CFG {
  reg32 const RESERVED;
  reg32 N[2];
};

struct GPIO_REG {
  reg32 fselN[GPIO_FUNC_REG_MAX];
  struct GPIO_CFG output_set;
  struct GPIO_CFG output_clear;
  struct GPIO_CFG level;
  struct GPIO_CFG ev_detect_status;
  struct GPIO_CFG re_detect_enable;
  struct GPIO_CFG fe_detect_enable;
  struct GPIO_CFG hi_detect_enable;
  struct GPIO_CFG lo_detect_enable;
  struct GPIO_CFG async_re_detect;
  struct GPIO_CFG async_fe_detect;
  reg32 const reserved[21];
  reg32 GPPUD_CNTRL[GPIO_PUPD_CTL_MAX];
};

#define GPIO_REG_MAP ((struct GPIO_REG *)(PBASE + GPIO_REG_OFFSET))

#endif /* GPIO_REG_BCM2711_H_ */