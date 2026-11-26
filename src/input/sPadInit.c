#include "game_pad.h"
extern s32 reset2;
extern void ZeroMemory(void *address, u32 size);

void sPadInit(void)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        ZeroMemory(&sPad[i], sizeof(PadState));
        sPad[i].field_08 = 0;
    }
    reset2 = 0;
}
