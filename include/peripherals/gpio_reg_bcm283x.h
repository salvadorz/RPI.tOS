/**
 * @file gpio_reg_bcm283x.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for GPIO Register Map on BCM283x
 *
 */

#ifndef GPIO_REG_BCM283X_H_
#define GPIO_REG_BCM283X_H_

// Includes
#include "common.h"

#include "base_addr.h"

#define GPIO_FUNC_REG_MAX   (6U)  /* GPFSEL0-5*/
#define GPIO_FSEL_BIT_MAX   (30U) /* FSEL BIT FIELD MAX n-PIN Cfg per Register*/
#define GPIO_FSEL_BIT_GRP   (3U)  /* 3 bits group for FSEL Cfg*/
#define GPIO_FSEL_BIT_MSK   ((1 << GPIO_FSEL_BIT_GRP) - 1) /* FSELn Bit field Mask*/
#define GPIO_PUDCLKn_MAX    (32u) /* PUDCLKn 0 - 31 and 32-53*/
#define GPIO_WAIT_TICKs     (150U)
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
  reg32 const reserved;
  reg32 GPPUD_En;
  reg32 GPPUDCLK_En[2];
};

#define GPIO_REG_MAP ((struct GPIO_REG *)(PBASE + GPIO_REG_OFFSET))

#endif /* GPIO_REG_BCM283X_H_ */