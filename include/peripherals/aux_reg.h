/**
 * @file aux_reg.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for Auxiliary peripherals Register Map
 *
 */

#ifndef AUX_REG_H_
#define AUX_REG_H_

// Includes
#include "common.h"

#include "base_addr.h"

#define AUX_REGISTER_OFFSET (0x00215000)

struct AUX_REG {
  reg32 AUX_IRQ;        /*Auxiliary Interrupt status*/
  reg32 AUX_ENABLES;    /*Auxiliary enables*/
  reg32 const reserved[14]; /*RESERVED*/
  reg32 AUX_MU_IO;      /*Mini Uart I/O Data*/
  reg32 AUX_MU_IER;     /*Mini Uart Interrupt Enable*/
  reg32 AUX_MU_IIR;     /*Mini Uart Interrupt Identify*/
  reg32 AUX_MU_LCR;     /*Mini Uart Line Control*/
  reg32 AUX_MU_MCR;     /*Mini Uart Modem Control*/
  reg32 AUX_MU_LSR;     /*Mini Uart Line Status*/
  reg32 AUX_MU_MSR;     /*Mini Uart Modem Status*/
  reg32 AUX_MU_SCRATCH; /*Mini Uart Scratch*/
  reg32 AUX_MU_CNTL;    /*Mini Uart Extra Control*/
  reg32 AUX_MU_STAT;    /*Mini Uart Extra Status*/
  reg32 AUX_MU_BAUD;    /*Mini Uart Baudrate*/
  reg32 AUX_SPI1_CNTL0; /*SPI 1 Control register 0*/
  reg32 AUX_SPI1_CNTL1; /*SPI 1 Control register 1*/
  reg32 AUX_SPI1_STAT;  /*SPI 1 Status*/
  reg32 AUX_SPI1_IO;    /*SPI 1 Data*/
  reg32 AUX_SPI1_PEEK;  /*SPI 1 Peek*/
  reg32 AUX_SPI2_CNTL0; /*SPI 2 Control register 0*/
  reg32 AUX_SPI2_CNTL1; /*SPI 2 Control register 1*/
};

#define AUX_REG_MAP ((struct AUX_REG *)(PBASE + AUX_REGISTER_OFFSET))
#endif /* AUX_REG_H_ */