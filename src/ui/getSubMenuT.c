#include "types.h"

extern s32 crN;
extern s32 sbN;
extern s32 sbT;
extern s32 menuMax[];

void getSubMenuT(void)
{
    s32 base[7] = {0, 2, 4, 5, 6, 7, -1};

    if (crN == -1) {
        sbT = -1;
        return;
    }
    if (sbN < 0)
        sbN = 0;
    if (sbN >= menuMax[crN])
        sbN = menuMax[crN];
    sbT = sbN + base[crN];
}
