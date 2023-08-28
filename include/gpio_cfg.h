/**
 * @file gpio_cfg.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for GPIO Configuration
 *
 */

#ifndef GPIO_CFG_H_
#define GPIO_CFG_H_

#define GPIO_CFG_SHIFT (8U)
#define GPIO_CFG_MASK  (0xFFU)
enum GPIO_FSEL_e {
  GPIO_FSEL_Input = 0,
  GPIO_FSEL_Output = 1,
  GPIO_FSEL_Alt0 = 4,
  GPIO_FSEL_Alt1 = 5,
  GPIO_FSEL_Alt2 = 6,
  GPIO_FSEL_Alt3 = 7,
  GPIO_FSEL_Alt4 = 3,
  GPIO_FSEL_Alt5 = 2
};

#define GPIO_GET_PIN_NUM(GPIO) ((GPIO) >> GPIO_CFG_SHIFT)
#define GPIO_GET_PIN_CFG(GPIO) ((GPIO) & GPIO_CFG_MASK)

// Default Cfg
#define GPIO0  ((0U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO1  ((1U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO2  ((2U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO3  ((3U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO4  ((4U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO5  ((5U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO6  ((6U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO7  ((7U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO8  ((8U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO9  ((9U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO10 ((10U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO11 ((11U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO12 ((12U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO13 ((13U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO14 ((14U << GPIO_CFG_SHIFT) | GPIO_FSEL_Alt5)
#define GPIO15 ((15U << GPIO_CFG_SHIFT) | GPIO_FSEL_Alt5)
#define GPIO16 ((16U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO17 ((17U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO18 ((18U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO19 ((19U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO20 ((20U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO21 ((21U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO22 ((22U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO23 ((23U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO24 ((24U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO25 ((25U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO26 ((26U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO27 ((27U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO28 ((28U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO29 ((29U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO30 ((30U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO31 ((31U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO32 ((32U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO33 ((33U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO34 ((34U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO35 ((35U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO36 ((36U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO37 ((37U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO38 ((38U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO39 ((39U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO40 ((40U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO41 ((41U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO42 ((42U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO43 ((43U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO44 ((44U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO45 ((45U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO46 ((46U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO47 ((47U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO48 ((48U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO49 ((49U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO50 ((50U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO51 ((51U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO52 ((52U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)
#define GPIO53 ((53U << GPIO_CFG_SHIFT) | GPIO_FSEL_Input)

#endif /* GPIO_CFG_H_ */