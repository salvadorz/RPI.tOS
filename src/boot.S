#include "mm.h"

.section ".text.boot"

.globl _start
_start:
    // Load Reg MPIDR_EL1 (pg. 1271)
    mrs x0, mpidr_el1
    // Mask last byte. Aff0 field Affinity level 0
    and x0, x0, #0xFF
    // if 0 jump to master
    cbz x0, master
    // jump to proc_hang otherwise
    b proc_hang

master:
    // arg src from memzero
    adr x0, bss_begin
    // load the end pox from bss to calculate the length
    adr x1, bss_end
    // substract to get the length (arg n)
    sub x1, x1, x0
    // call memzero
    bl memzero

    mov sp, #LOW_MEMORY
    bl kernel_main
    // Should not reach here
    b  proc_hang

proc_hang:
    // wait for event
    wfe
    b proc_hang