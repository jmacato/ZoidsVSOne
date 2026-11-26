#include "game_pad.h"

extern PadState *sPad1;
extern s32 VsTime;

void sub6(void)
{
    if (sPad1->left)
        VsTime--;
    if (sPad1->right)
        VsTime++;
    if (VsTime < 0)
        VsTime = 0;
    if (VsTime > 4)
        VsTime = 4;
}
