.text
.align 2
.thumb

.global sprintf
sprintf:
    push    {lr}
    blx     0x020D7510
    pop     {pc}

.global debugsyscall
debugsyscall:
    swi     0xFC
    bx      lr
