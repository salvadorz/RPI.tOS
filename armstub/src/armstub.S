/* https://github.com/raspberrypi/tools/blob/master/armstubs/armstub8.S */
.globl _start
_start:
    // Loads kernel_entry32 address into w0.
    ldr w0, kernel_entry32
    // jump to address contained in x0.
    br x0

.ltorg

// .org makes the base address (offset) for next instructions.

.org 0xf0
.globl stub_magic
stub_magic:
    // Defines a word (32 bits) with hexadecimal 0x5afe570b.
    .word 0x5afe570b

.org 0xf4
.globl stub_version
stub_version:
    .word 0

.org 0xfc
.globl kernel_entry32
kernel_entry32:
    .word 0x0