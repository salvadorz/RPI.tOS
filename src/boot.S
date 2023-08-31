#include "rpi_cfg.h"
#include "mm.h"

#if MULTICORE
.data
barrier:    .byte 0  // uint_8 barrier=0
            .align 2 // Align 4 bytes 
#endif

.section ".text.boot"

.globl _start
_start:
    // Load Reg MPIDR_EL1 (pg. 1271)
    mrs x0, mpidr_el1
    // Mask last byte. Aff0 field Affinity level 0
    and x0, x0, #0xFF
    // if 0 (Core 0) jump to do bss_init
    cbz x0, bss_init
#if !(MULTICORE)
    // jump to proc_hang otherwise
    b proc_hang
#else
    b wait

wait:
    // Wait for BSS init
    // uint8_t lock_sts = *barrier;
	ldr x1, =barrier
    // load the byte in w0
	ldrb w0, [x1]
    // if (1 == lock_sts)
	cmp w0, #1
    // goto master
	beq master
    // else
	b wait
#endif

bss_init:
    // arg src from memzero
    adr x0, bss_begin
    // load the end pox from bss to calculate the length
    adr x1, bss_end
    // substract to get the length (arg n)
    sub x1, x1, x0
    // call memzero
    bl memzero

#if MULTICORE
	// Tell other Cores BSS is ready
	mov w0, #1 //uint8_t free = 1
    // *barrier = free
	ldr x1, =barrier
    // store w0 value into w1 address
	strb w0, [x1]
    // master()
	b master

master:
	// Use the CPU ID to determine the stack location: 
	// CPU #0: sp = (COREx + 1) * #LOW_MEMORY, CPU #1: sp = (Core2 + 1) * #LOW_MEMORY, etc
	mov	x0, #LOW_MEMORY 
	// Get Core Number
    mrs x1, mpidr_el1
	and x1, x1, #0xFF
    // Core N + 1
	add x1, x1, #1
    // (CoreN + 1) * LOW_MEM
	mul x0, x0, x1
    // Assigning Stack to each core
	mov sp, x0

	bl	kernel_multi_main
	b 	proc_hang   // Should not reach here
#else

master:
    mov sp, #LOW_MEMORY
    bl kernel_main
    // Should not reach here
    b  proc_hang
#endif
proc_hang:
    // wait for event
    wfe
    b proc_hang