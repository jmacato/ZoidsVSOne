#include "game_pad.h"

extern PadState *sPad3;
extern PadState *sPad4;
extern s32 (*sPad4dbgFunc)(void);
extern s32 reset2;
extern s32 sPad4dbgMenu(void);
extern void dInt(void);
extern void HSD_PadRenewStatus(void);
extern void sPadGet1(s32 port);
extern s32 IsReset(void);
extern void TEA_HotReset(u32 code);

static inline s32 sPadChkReset(void)
{
    s32 reset = IsReset();

    return reset;
}

void sPadAll(void)
{
    s32 i;

    dInt();
    HSD_PadRenewStatus();
    for (i = 0; i < 2; i++) {
        sPadGet1(i);
    }
    if (sPad4->connected == 0) {
        sPad4dbgFunc = 0;
    } else if (sPad4->previous_connected == 0) {
        sPad4dbgFunc = sPad4dbgMenu;
    }
    sPad3->reset_hold_frames = 0;
    sPad4->reset_hold_frames = 0;
    if (sPadChkReset() != 0) {
        reset2 = 1;
    } else if (reset2 != 0) {
        reset2 = 0;
        TEA_HotReset(0);
    }
}
