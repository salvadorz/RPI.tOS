.globl delay_ticks
delay_ticks:
    // substract 1 from x0 (x0 -= 1)
    subs x0, x0, #1
    // if not 0 then go to..
    bne delay_ticks
    ret

.globl write_reg
write_reg:
    // Store the 32reg w1 in dst (base)address x0 (64b) 
    str w1, [x0]
    ret

.globl read_reg
read_reg:
    //Load the content of address x0 in w0
    ldr w0, [x0]
    ret

.globl get_proc_id
get_proc_id:
    mrs x0, mpidr_el1
    and x0, x0, #0xFF
    ret

.globl get_exc_lvl
get_exc_lvl:
    mrs x0, CurrentEL
    //Logical shifting to Right
    lsr x0, x0, #2
    ret