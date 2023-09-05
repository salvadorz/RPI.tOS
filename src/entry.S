#include "entry.h"

/** Macro which calls `kernel_entry` macro and prepares 3 args. 
 *  first arg: `type` is the 0-15 Exception type from `entry.h`
 *  second arg: the Exception Syndrome Reg (pg. 6438 Armv8-A_RM)
 *  third arg: Used when is a sync expception as contain the address
 *  of the instruction been executed when the exception was generated.
 */
    .macro handle_invalid_entry type
    kernel_entry
    mov x0, #\type
    mrs x1, esr_el1
    mrs x2, elr_el1
    bl  irq_invalid_entry_message
    b   err_hang
    .endm

    // macro `ventry` to create entries in the vector table with alignment of 0x80 (2^7)
    .macro  ventry    label
    .align  7
    b   \label
    .endm
/** Saving the preocessor state
 * stores registers x0- x30
 */
    .macro  kernel_entry
    sub sp, sp, #S_FRAME_SIZE
    stp x0, x1, [sp, #16 * 0]
    stp x2, x3, [sp, #16 * 1]
    stp x4, x5, [sp, #16 * 2]
    stp x6, x7, [sp, #16 * 3]
    stp x8, x9, [sp, #16 * 4]
    stp x10, x11, [sp, #16 * 5]
    stp x12, x13, [sp, #16 * 6]
    stp x14, x15, [sp, #16 * 7]
    stp x16, x17, [sp, #16 * 8]
    stp x18, x19, [sp, #16 * 9]
    stp x20, x21, [sp, #16 * 10]
    stp x22, x23, [sp, #16 * 11]
    stp x24, x25, [sp, #16 * 12]
    stp x26, x27, [sp, #16 * 13]
    stp x28, x29, [sp, #16 * 14]
    str x30, [sp, #16 * 15] 
    .endm
/** Restoring the preocessor state
 * loads registers x0- x30
 */
    .macro  kernel_exit
    ldp x0, x1, [sp, #16 * 0]
    ldp x2, x3, [sp, #16 * 1]
    ldp x4, x5, [sp, #16 * 2]
    ldp x6, x7, [sp, #16 * 3]
    ldp x8, x9, [sp, #16 * 4]
    ldp x10, x11, [sp, #16 * 5]
    ldp x12, x13, [sp, #16 * 6]
    ldp x14, x15, [sp, #16 * 7]
    ldp x16, x17, [sp, #16 * 8]
    ldp x18, x19, [sp, #16 * 9]
    ldp x20, x21, [sp, #16 * 10]
    ldp x22, x23, [sp, #16 * 11]
    ldp x24, x25, [sp, #16 * 12]
    ldp x26, x27, [sp, #16 * 13]
    ldp x28, x29, [sp, #16 * 14]
    ldr x30, [sp, #16 * 15] 
    add sp, sp, #S_FRAME_SIZE    
    eret
    .endm


/*
 * Exception vectors. (alligned 2048, 0x80 times 16 entries)
 */
.align  11
.globl vectors 
vectors:
    ventry  sync_invalid_el1t     // Synchronous EL1t
    ventry  irq_invalid_el1t      // IRQ EL1t
    ventry  fiq_invalid_el1t      // FIQ EL1t
    ventry  err_invalid_el1t      // Error EL1t

    ventry  sync_invalid_el1h     // Synchronous EL1h
    ventry  irq_el1h_handle       // IRQ EL1h         ** Valid ISR **
    ventry  fiq_invalid_el1h      // FIQ EL1h
    ventry  err_invalid_el1h      // Error EL1h

    ventry  sync_invalid_el0_64   // Synchronous 64-bit EL0
    ventry  irq_invalid_el0_64    // IRQ 64-bit EL0
    ventry  fiq_invalid_el0_64    // FIQ 64-bit EL0
    ventry  err_invalid_el0_64    // Error 64-bit EL0

    ventry  sync_invalid_el0_32   // Synchronous 32-bit EL0
    ventry  irq_invalid_el0_32    // IRQ 32-bit EL0
    ventry  fiq_invalid_el0_32    // FIQ 32-bit EL0
    ventry  err_invalid_el0_32    // Error 32-bit EL0

sync_invalid_el1t:
    handle_invalid_entry  SYNC_INVALID_EL1t

irq_invalid_el1t:
    handle_invalid_entry  IRQ_INVALID_EL1t

fiq_invalid_el1t:
    handle_invalid_entry  FIQ_INVALID_EL1t

err_invalid_el1t:
    handle_invalid_entry  ERR_INVALID_EL1t

sync_invalid_el1h:
    handle_invalid_entry  SYNC_INVALID_EL1h

fiq_invalid_el1h:
    handle_invalid_entry  FIQ_INVALID_EL1h

err_invalid_el1h:
    handle_invalid_entry  ERR_INVALID_EL1h

sync_invalid_el0_64:
    handle_invalid_entry  SYNC_INVALID_EL0_64

irq_invalid_el0_64:
    handle_invalid_entry  IRQ_INVALID_EL0_64

fiq_invalid_el0_64:
    handle_invalid_entry  FIQ_INVALID_EL0_64

err_invalid_el0_64:
    handle_invalid_entry  ERR_INVALID_EL0_64

sync_invalid_el0_32:
    handle_invalid_entry  SYNC_INVALID_EL0_32

irq_invalid_el0_32:
    handle_invalid_entry  IRQ_INVALID_EL0_32

fiq_invalid_el0_32:
    handle_invalid_entry  FIQ_INVALID_EL0_32

err_invalid_el0_32:
    handle_invalid_entry  ERR_INVALID_EL0_32

irq_el1h_handle:
    kernel_entry 
    bl  irq_handler
    kernel_exit 

.globl err_hang
err_hang: b err_hang