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