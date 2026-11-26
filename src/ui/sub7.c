#include "game_pad.h"

extern PadState *sPad1;
extern s32 VsMode;

void sub7(void)
{
    if (sPad1->left)
        VsMode = 0;
    if (sPad1->right)
        VsMode = 1;
}
