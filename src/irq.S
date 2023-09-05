#include "irq.h"

.globl irq_vectors_init
irq_vectors_init:
    adr	   x0, vectors     // load VBAR_EL1 with virtual
    msr	   vbar_el1, x0    // (pg. 7161. Armv8-A RM. vector table address
    ret

// Unmasking Interrupts/Exceptions
.globl irq_enable
irq_enable:
    msr    daifclr, #IRQs_EXCEPTION
    ret

// Masking Interrupts/Exceptions
.globl irq_disable
irq_disable:
    msr    daifset, #IRQs_EXCEPTION
    ret