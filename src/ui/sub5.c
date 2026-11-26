#include "game_pad.h"

extern PadState *sPad1;
extern s32 rumble;
extern s32 rumbleTm;

void sub5(void)
{
    s32 previous = rumble;
    if (sPad1->left)
        rumble = 1;
    if (sPad1->right)
        rumble = 0;
    if (previous != 0)
        return;
    if (rumble == 0)
        return;
    rumbleTm = 30;
}
