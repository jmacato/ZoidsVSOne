#include "types.h"

extern u8 menubackanm[60], menufarmanm[20];
extern s32 menuanmend, menu_StageUpDownFlag;
extern void menu_sDispBattleFarm(void);

s32 menu_sDispBattleStageDown(s32 mode)
{
    if (mode == 1)
        menubackanm[1] = 2;
    else
        menubackanm[1] = 3;
    return menu_StageUpDownFlag;
}

void menu_sDispBattleFarmStageDown(s32 mode)
{
    menuanmend = 0;
    if (mode == 1)
        menubackanm[1] = 2;
    else
        menubackanm[1] = 3;
    while (menuanmend == 0)
        menu_sDispBattleFarm();
    menuanmend = 0;
}

void menuerasewait(s16 animation)
{
    menuanmend = 0;
    menufarmanm[animation] = 2;
    while (menuanmend == 0)
        menu_sDispBattleFarm();
    menuanmend = 0;
}
