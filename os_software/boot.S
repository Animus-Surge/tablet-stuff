.section ".text.boot"  // Make sure the linker puts this at the start of the kernel image

.globl _start  // Execution starts here

.org 0x80000

PUT32:
    str w1, [x0]
    ret

GET32:
    ldr w0, [x0]
    ret

DELAY:
    subs x0, x0, #1
    bne DELAY
    ret

_start:
    ldr x5, =_start
    mov sp, x5

    ldr x5, =__bss_start
    ldr w6, =__bss_size
1:  cbz w6, 2f
    str xzr, [x5], #8
    sub w6, w6, #1
    cbnz w6, 1b

2:  bl kmain

halt:
    wfe
    b halt
