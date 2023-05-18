.text
.align 2
.thumb

.thumb_func
.global Battle_MapBToFlee
Battle_MapBToFlee:
    mov     r3, r1
    tst     r3, r5
    bne     Battle_ReturnBack
    tst     r1, r7
    beq     Battle_ReturnZero
    ldrb    r3, [r0, #1]
    cmp     r3, #1
    beq     Battle_CheckXCoord

Battle_SetToRun:
    mov     r3, #1
    strb    r3, [r0, #1]
    strb    r3, [r0, #2]
    mov     r5, #2
    b       Battle_ReturnBack

Battle_CheckXCoord:
    ldrb    r3, [r0, #2]
    cmp     r3, #1
    bne     Battle_SetToRun
    mov     r5, #1

Battle_ReturnBack:
    ldr     r3, =0x0226CCAA | 1
    bx      r3

Battle_ReturnZero:
    ldr     r3, =0x0226CCA6 | 1
    bx      r3
