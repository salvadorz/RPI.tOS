SECTIONS
{
    /* Boot code of the program */
    .text.boot : { *(.text.boot) }

    /* Main program code */
    .text : { *(.text) }

    /* Section Read-only data (rodata) */
    .rodata : { *(.rodata) }

    /* Section Initialized data (data) */
    .data : { *(.data) }

    /* Alignment: Ensure that the current address is a multiple of 8 */
    . = ALIGN(0x8);

    /* Define the start and end of the .bss section for uninitialized data */
    bss_begin = .;
    .bss : { *(.bss*) }
    bss_end = .;
}
