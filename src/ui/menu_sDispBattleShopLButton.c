#include "types.h"

extern s16 menumode;
extern void menu_sDispBattleShopLButtonAnm(s32 button);

void menu_sDispBattleShopLButton(void)
{
    if (menumode != 0) {
        menu_sDispBattleShopLButtonAnm(0);
        menu_sDispBattleShopLButtonAnm(1);
        menu_sDispBattleShopLButtonAnm(2);
    }
}
