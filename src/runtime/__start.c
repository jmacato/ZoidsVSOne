void DBInit(void);
void OSInit(void);
void __check_pad3(void);
void __init_data(void);
void __init_hardware(void);
void __init_registers(void);
void __init_user(void);
void exit(void);
void main(void);

asm void __start(void)
{
    nofralloc
    bl __init_registers
    bl __init_hardware
    li r0, -1
    stwu r1, -8(r1)
    stw r0, 4(r1)
    stw r0, 0(r1)
    bl __init_data
    li r0, 0
    lis r6, -0x8000
    addi r6, r6, 0x44
    stw r0, 0(r6)
    lis r6, -0x8000
    addi r6, r6, 0xf4
    lwz r6, 0(r6)
    cmplwi r6, 0
    beq lab_48
    lwz r7, 0xc(r6)
    b lab_68
lab_48:
    lis r5, -0x8000
    addi r5, r5, 0x34
    lwz r5, 0(r5)
    cmplwi r5, 0
    beq lab_90
    lis r7, -0x8000
    addi r7, r7, 0x30e8
    lwz r7, 0(r7)
lab_68:
    li r5, 0
    cmplwi r7, 2
    beq lab_80
    cmplwi r7, 3
    bne lab_90
    li r5, 1
lab_80:
    lis r6, -0x7ff9
    addi r6, r6, -0x1e7c
    mtspr 8, r6
    blrl
lab_90:
    lis r6, -0x8000
    addi r6, r6, 0xf4
    lwz r5, 0(r6)
    cmplwi r5, 0
    bc 13, 2, lab_f0
    lwz r6, 8(r5)
    cmplwi r6, 0
    bc 13, 2, lab_f0
    add r6, r5, r6
    lwz r14, 0(r6)
    cmplwi r14, 0
    beq lab_f0
    addi r15, r6, 4
    mtspr 9, r14
lab_c8:
    addi r6, r6, 4
    lwz r7, 0(r6)
    add r7, r7, r5
    stw r7, 0(r6)
    bdnz lab_c8
    lis r5, -0x8000
    addi r5, r5, 0x34
    rlwinm r7, r15, 0, 0, 0x1a
    stw r7, 0(r5)
    b lab_f8
lab_f0:
    li r14, 0
    li r15, 0
lab_f8:
    bl DBInit
    bl OSInit
    lis r4, -0x8000
    addi r4, r4, 0x30e6
    lhz r3, 0(r4)
    andi. r5, r3, 0x8000
    beq lab_120
    andi. r3, r3, 0x7fff
    cmplwi r3, 1
    bne lab_124
lab_120:
    bl __check_pad3
lab_124:
    bl __init_user
    mr r3, r14
    mr r4, r15
    bl main
    b exit
}
