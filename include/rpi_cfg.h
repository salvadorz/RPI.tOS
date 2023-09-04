 /**
 * @file rpi_cfg.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for General RPI Configuration
 *
 */

#ifndef RPI_CFG_H_
#define RPI_CFG_H_

#ifndef MULTICORE
  #define MULTICORE (0U)
#endif
#define CORE0     (0U)
#define CORE1     (1U)
#define CORE2     (2U)
#define CORE3     (3U)
#define CORE_MAX  (4U)

#define DEBUG     (0U)

#endif /* RPI_CFG_H_ */