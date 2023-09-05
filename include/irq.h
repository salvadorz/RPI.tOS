/**
 * @file irq.h
 * @author Salvador Z
 * @version 1.0
 * @brief File for IRQ declarations
 *
 */

#ifndef IRQ_H_
#define IRQ_H_

/** DAIF Bit selection
 */
#define DEBUG_EXCEPTION (1 << 3) // Special type of sync exceptions
#define ABORT_EXCEPTION (1 << 2) // (Un)mask SErrors (async aborts)
#define IRQs_EXCEPTION  (1 << 1) // IRQ Mask/Unmaks bit exception
#define FIQs_EXCEPTION  (1 << 0) // FIQ bit for Mask/Unmask bit exception

/** ARM Interrupts Table
 * [IRQ0-63]
 */
#define SYS_TIMER_IRQ_0 (1 << 0) /* Do not USE as GPU use it*/
#define SYS_TIMER_IRQ_1 (1 << 1) /* System Timer Match 1 IRQ */
#define SYS_TIMER_IRQ_2 (1 << 2) /* Do not USE as GPU use it*/
#define SYS_TIMER_IRQ_3 (1 << 3) /* System Timer Match 3 IRQ */
#define USB_CNTRLLR_IRQ (1 << 9) /* Usb Controller IRQ */
#define AUX_mUART_IRQ   (1 <<29) /* Auxiliary (miniUART) and SPIx IRQ */

#ifndef __ASSEMBLER__
void irq_interrupt_controller_enable(void);

/*  Implemented in irq.S */
void irq_vectors_init(void);
void irq_enable(void);
void irq_disable(void);
#endif

#endif /* IRQ_H_ */