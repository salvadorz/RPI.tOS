#include "gpio.h"
#include "utils.h"

void gpio_pin_set_func(u8 pinNumber, GPIO_FSEL_t func) {
  /*There are max 54pins the Function Select needs 3 bits the FSEL{n} field
  determins the functionality of the n-th GPIO pin. */
  // Calculates the startBit in the reg
  u8 const startBit = (pinNumber * GPIO_FSEL_BIT_GRP) % GPIO_FSEL_BIT_MAX;
  u8 const sel_offset = GPIO_GET_FSELn(pinNumber);

  u32 fselN_reg = GPIO_REG_MAP->fselN[sel_offset];
  fselN_reg = CLR_REG(fselN_reg, GPIO_FSEL_BIT_MSK, startBit);
  fselN_reg = SET_REG(fselN_reg, func, startBit);

  GPIO_REG_MAP->fselN[sel_offset] = fselN_reg;
}

#if (RPI_VERSION == 4)
void gpio_pin_enable(u8 pinNumber) {
  // To find the GPIO_PUP_PDN_CNTRL_REG N register
  u8 gpio_pud_cntrl_N = (pinNumber >> GPIO_PUPD_CTL_MAX);    // pinNumber / 16
  u8 gpio_pud_strtBit = (pinNumber % GPIO_PUPD_PIN_GRP) * 2; // Bit GPIO_PUP_PDN_CNTRL0-15 (0-30)

  // BCM2711 Ch5.2 GPIO Pull-up/down Control Registers (pg. 74)
  u32 GPIO_PUP_PDN_CNTRL_REGx = GPIO_REG_MAP->GPPUD_CNTRL[gpio_pud_cntrl_N];

  GPIO_PUP_PDN_CNTRL_REGx =
      CLR_REG(GPIO_PUP_PDN_CNTRL_REGx, GPIO_PUD_pull_mask, gpio_pud_strtBit);
  GPIO_PUP_PDN_CNTRL_REGx =
      SET_REG(GPIO_PUP_PDN_CNTRL_REGx, GPIO_PUD_disable_pud, gpio_pud_strtBit);

  GPIO_REG_MAP->GPPUD_CNTRL[gpio_pud_cntrl_N] = GPIO_PUP_PDN_CNTRL_REGx;
}
#else
void gpio_pin_enable(u8 pinNumber) {
  u8 gppudclkN = 0;
  // If >= 32 goes to the gppudclk1 reg
  if (pinNumber >= GPIO_PUDCLKn_MAX) {
    gppudclkN = 1;
    pinNumber -= GPIO_PUDCLKn_MAX; // Instead of % 32
  }
  // BCM2835 Ch6 GPIO Pull-up/down Clock Registers (pg. 101)
  GPIO_REG_MAP->GPPUD_En = GPIO_PUD_disable_pud;
  delay_ticks(GPIO_WAIT_TICKs);
  GPIO_REG_MAP->GPPUDCLK_En[gppudclkN] = SET_BIT(pinNumber);
  delay_ticks(GPIO_WAIT_TICKs);
  GPIO_REG_MAP->GPPUD_En = GPIO_PUD_disable_pud;
  GPIO_REG_MAP->GPPUDCLK_En[gppudclkN] = 0;
}
#endif