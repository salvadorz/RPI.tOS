/**
 * @file gpio.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for gpio driver
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

// Includes
#include "common.h"
#include "gpio_cfg.h"
#if (RPI_VERSION == 4)
  #include "peripherals/gpio_reg_bcm2711.h"
#else
  #include "peripherals/gpio_reg_bcm283x.h"
#endif

#define GPIO_GET_FSELn(pin) (pin / 10)

typedef enum GPIO_FSEL_e GPIO_FSEL_t;

typedef enum GPIO_PUD_e {
  GPIO_PUD_disable_pud = 0, /* Disable pull-up/down */
  GPIO_PUD_pull_dwn_en = 1, /* Enable pull-down */
  GPIO_PUD_pull_up_en = 2,  /* Enable pull-up */
  GPIO_PUD_pull_mask = 3,   /* Mask for max value */
} GPIO_PUD_t;

void gpio_pin_set_func(u8 pinNumber, GPIO_FSEL_t func);

void gpio_pin_enable(u8 pinNumber);

#endif /* GPIO_H_ */