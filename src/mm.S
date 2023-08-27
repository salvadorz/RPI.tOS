.globl memzero
memzero:
    // Store 0 at address pointed by x0 then increment 8 pox (u64)
    str xzr, [x0], #8
    // Substract 8 from the counter at x1
    subs x1, x1, #8
    // if x > 0 go to memzero
    b.gt memzero
    ret