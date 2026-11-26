#include "game_pad.h"

extern PadState *sPad1;
extern s32 VolSe;
extern s32 VolSeTBL[];
extern s16 TEA_SEVOL;
extern s32 SE_TableList[];
extern void TEA_SeOn(u16 se, s32 a, s32 b);

void sub4(void)
{
    if (sPad1->left != 0)
        VolSe--;
    if (sPad1->right != 0)
        VolSe++;
    if (VolSe < 0)
        VolSe = 0;
    if (VolSe >= 10)
        VolSe = 10;
    TEA_SEVOL = VolSeTBL[VolSe];
    if (sPad1->pressed_a != 0) {
        if (SE_TableList[29] >= 0)
            TEA_SeOn(SE_TableList[29], 0, 1);
    }
}
