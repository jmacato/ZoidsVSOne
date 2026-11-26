#include "game_pad.h"

extern PadState *sPad1;
extern s32 VolBgm;
extern s32 TestBgm;
extern s32 VolBgmTBL[];
extern s16 TEA_BGMVOL;
extern void TeaBgm(s16 track);

void sub0(void)
{
    if (sPad1->left != 0)
        VolBgm--;
    if (sPad1->right != 0)
        VolBgm++;
    if (VolBgm < 0)
        VolBgm = 0;
    if (VolBgm >= 10)
        VolBgm = 10;
    TEA_BGMVOL = VolBgmTBL[VolBgm];
    if (sPad1->pressed_a != 0) {
        TeaBgm(-1);
        TeaBgm(TestBgm);
    }
}
