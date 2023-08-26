/**
 * @file base_addr.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for SoC base Address
 *
 */

#ifndef BASE_ADDR_H_
#define BASE_ADDR_H_

#define RPI_MODEL_3B (3U)
#define RPI_MODEL_4B (4U)


#if (RPI_VERSION == RPI_MODEL_3B)
  #define PBASE 0x3F000000
  // https://github.com/raspberrypi/linux/blob/e89e7655a197d28df49da2be7e2003436cf52197/arch/arm/boot/dts/bcm2837.dtsi#L9

#elif (RPI_VERSION == RPI_MODEL_4B)
  #define PBASE 0xFE000000
  // https://github.com/raspberrypi/linux/blob/e89e7655a197d28df49da2be7e2003436cf52197/arch/arm/boot/dts/bcm2711.dtsi#L41C29-L41C39

#else
  #define PBASE 0
  #error RPI_VERSION NOT DEFINED

#endif

#endif /* BASE_ADDR_H_ */
