#include "exi.h"
#include "os.h"
#include "os_interrupt.h"

#define FALSE 0

extern volatile u32 __PIRegs[16] : 0xCC003000;
extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern int printf(const char *, ...);
extern s32 AmcEXIImm(void *buf, s32 len, u32 type, EXICallback callback);
extern void AmcEXISync(void);
extern EXICallback AmcEXISetExiCallback(EXICallback callback);
extern s32 AmcEXISelect(u32 freq);
extern s32 AmcEXIDeselect(void);
extern void AmcEXIEnableInterrupts(void);
extern void AmcEXIInit(void);

static volatile u8 ucEXI2InputPending;
static volatile u8 *pucEXI2InputPending = &ucEXI2InputPending;
static s32 fExi2Selected;
static void (*TRK_Callback)(s32, OSContext *);

void EXI2_CallBack(s32 chan, OSContext *context)
{
    *pucEXI2InputPending = 1;
    if (TRK_Callback)
        TRK_Callback(0, context);
}

void EXI2_EnableInterrupts(void)
{
    AmcEXISetExiCallback(EXI2_CallBack);
    AmcEXIEnableInterrupts();
}

void EXI2_Reserve(void)
{
}

void EXI2_Unreserve(void)
{
}

s32 AMC_IsStub(void)
{
    return 1;
}
