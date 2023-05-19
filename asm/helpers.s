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

.force_thumb
.syntax unified
.global __aeabi_idiv
.thumb_func
.type __aeabi_idiv,function
__aeabi_idiv:
.force_thumb
.syntax unified
.global __aeabi_idivmod
.thumb_func
.type __aeabi_idivmod,function
__aeabi_idivmod:
.force_thumb
.syntax unified
.global __aeabi_uidiv
.thumb_func
.type __aeabi_uidiv,function
__aeabi_uidiv:
    push    {lr}
    blx     0x020E1F6C
    pop     {pc}
.size __aeabi_idiv, . - __aeabi_idiv
.size __aeabi_idivmod, . - __aeabi_idivmod
.size __aeabi_uidiv, . - __aeabi_uidiv

.force_thumb
.syntax unified
.global memcpy
.thumb_func
.type memcpy,function
memcpy:
    push    {lr}
    blx     0x020D50B8
    pop     {pc}
.size memcpy, . - memcpy
