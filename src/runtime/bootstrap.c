/* Reference:
 * https://github.com/doldecomp/sms/blob/main/libs/dolphin/src/os/__start.c. */
#include "runtime_string.h"
#include "os_reset.h"
#include "asm_ops.h"
#pragma peephole off
typedef struct RomCopyInfo {
    char *rom;
    char *addr;
    unsigned int size;
} RomCopyInfo;
typedef struct BssInitInfo {
    char *addr;
    unsigned int size;
} BssInitInfo;
__declspec(section ".init") extern RomCopyInfo _rom_copy_info[];
__declspec(section ".init") extern BssInitInfo _bss_init_info[];
extern void __flush_cache(void *, unsigned long);
extern void __OSPSInit(void);
extern void __OSCacheInit(void);
extern char _stack_addr[];
extern char _SDA_BASE_[];
extern char _SDA2_BASE_[];
__declspec(section ".init") static inline void
copy_rom_section(void *dst, const void *src, unsigned long size)
{
    if (size && dst != src) {
        memcpy(dst, src, size);
        __flush_cache(dst, size);
    }
}
__declspec(section ".init") static inline void init_bss_section(void *dst,
                                                                unsigned long size)
{
    if (size)
        memset(dst, 0, size);
}
__declspec(section ".init") static void __init_registers(void)
{
    ASM_INSN(lis r1, _stack_addr@h);
    ASM_INSN(ori r1, r1, _stack_addr@l);
    ASM_INSN(lis r2, _SDA2_BASE_@h);
    ASM_INSN(ori r2, r2, _SDA2_BASE_@l);
    ASM_INSN(lis r13, _SDA_BASE_@h);
    ASM_INSN(ori r13, r13, _SDA_BASE_@l);
}
__declspec(section ".init") static void __init_data(void)
{
    RomCopyInfo *dci;
    BssInitInfo *bii;
    dci = _rom_copy_info;
    while (1) {
        if (dci->size == 0)
            break;
        copy_rom_section(dci->addr, dci->rom, dci->size);
        dci++;
    }
    bii = _bss_init_info;
    while (1) {
        if (bii->size == 0)
            break;
        init_bss_section(bii->addr, bii->size);
        bii++;
    }
}
#pragma peephole on
__declspec(section ".init") static void __check_pad3(void)
{
    if ((*(unsigned short *)0x800030E4 & 0x0EEF) == 0x0EEF)
        OSResetSystem(0, 0, 0);
}
__declspec(section ".init") void __flush_cache(void *addr, unsigned long size)
{
    ASM_INSN(lis r5, -1);
    ASM_INSN(ori r5, r5, 65521);
    ASM_INSN(and r5, r5, r3);
    ASM_INSN(sub r3, r3, r5);
    ASM_INSN(add r4, r4, r3);
    ASM_INSN(l5444: dcbst r0, r5);
    ASM_INSN(sync);
    ASM_INSN(icbi r0, r5);
    ASM_INSN(addic r5, r5, 8);
    ASM_INSN(addic. r4, r4, -8);
    ASM_INSN(bge l5444);
    ASM_INSN(isync);
}
__declspec(section ".init") asm void __init_hardware(void)
{
    nofralloc
    mfmsr r0
    ori r0, r0, 0x2000
    mtmsr r0
    mfspr r31, 8
    bl __OSPSInit
    bl __OSCacheInit
    mtspr 8, r31
    blr
}
