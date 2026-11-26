#include "game_pad.h"

extern PadState *sPad1;
extern s32 TestBgm;
extern s16 TEA_BGMMAXNUM;
extern void TeaBgm(s16 track);

void sub1(void)
{
    if (sPad1->left != 0)
        TestBgm--;
    if (sPad1->right != 0)
        TestBgm++;
    if (TestBgm <= 0)
        TestBgm = 1;
    if (TestBgm >= TEA_BGMMAXNUM - 1)
        TestBgm = TEA_BGMMAXNUM - 1;
    if (sPad1->pressed_a != 0) {
        TeaBgm(-1);
        TeaBgm(TestBgm);
    }
}
