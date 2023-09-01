#include "rpi_cfg.h"
#include "mm.h"
#include "arm/sys_cfg.h"

#if (!MULTICORE)

.section ".text.boot"

.globl _start
_start:
    // Load Reg MPIDR_EL1 (pg. 1271)
    mrs x0, mpidr_el1
    // Mask last byte. Aff0 field Affinity level 0
    and x0, x0, #0xFF
    // if 0 (Core 0) jump to do el_cfg (exception level cfg)
    cbz x0, el_cfg
    // jump to proc_hang otherwise
    b proc_hang

// System in EL3 Secure State, Core 0 Cfg EL1
el_cfg:
    // Wr sctrl_el1 with SCTLR_EL1_REG_CFG
    ldr x0, =SCTLR_EL1_REG_CFG // Lendian, No Caches (I/D) and No MMU
    msr sctlr_el1, x0          // Cfg processor parameters when operates at EL1

    // Wr hcr_el2 with HCR_EL2_REG_CFG
    ldr x0, =HCR_EL2_REG_CFG  // Execution state AArch64 mode
    msr hcr_el2, x0           // Hypervisor Cfg Reg

    // Wr scr_el3 with SCR_EL3_REG_CFG
    ldr x0, =SCR_EL3_REG_CFG  // Non-secure state from EL2-0 and AArch64 lower level
    msr scr_el3, x0

    // Wr spsr_el3 with SPSR_REG_CFG
    ldr x0, =SPSR_REG_CFG    // Masking ISR and dedicated SP for EL1
    msr spsr_el3, x0         // Prepare (manually) processor state. 

    // store in elr_el3 the address jump to
    adr x0, el1_entry        // Prepare the jump to label
    msr elr_el3, x0          // Exception Link Register (EL3)

    // jump to el1 (restores processor state from SPSR_EL3)
    eret

el1_entry:
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
//----------------------------SINGLE CORE-----------------------/
#else

.data
barrier:    .byte 0  // uint_8 barrier=0
            .align 2 // Align 4 bytes 

.section ".text.boot"

.globl _start
_start:
    // Load Reg MPIDR_EL1 (pg. 1271)
    mrs x0, mpidr_el1
    // Mask last byte. Aff0 field Affinity level 0
    and x0, x0, #0xFF
    // if 0 (Core 0) jump to do el_cfg (exception level cfg)
    cbz x0, el_cfg
    // jump to wait otherwise
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

// System in EL3 Secure State, Core 0 Cfg EL1
el_cfg:
    // Wr sctlr_el1 with SCTLR_EL1_REG_CFG
    ldr x0, =SCTLR_EL1_REG_CFG
    msr sctlr_el1, x0

    // Wr hcr_el2 with HCR_EL2_REG_CFG
    ldr x0, =HCR_EL2_REG_CFG
    msr hcr_el2, x0

    // Wr scr_el3 with SCR_EL3_REG_CFG
    ldr x0, =SCR_EL3_REG_CFG
    msr scr_el3, x0

    // Wr spsr_el3 with SPSR_REG_CFG
    ldr x0, =SPSR_REG_CFG
    msr spsr_el3, x0

    // store in elr_el3 the address jump to
    adr x0, el1_entry
    msr elr_el3, x0

    // jump to el1 (restores processor state from SPSR_EL3)
    eret

el1_entry:
    // arg src from memzero
    adr x0, bss_begin
    // load the end pox from bss to calculate the length
    adr x1, bss_end
    // substract to get the length (arg n)
    sub x1, x1, x0
    // call memzero
    bl memzero

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

proc_hang:
    // wait for event
    wfe
    b proc_hang

#endif