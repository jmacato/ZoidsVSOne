#include "types.h"

extern s16 menumode;
extern void menu_sDispBattleShopLButtonZoid(void);
extern void menu_sDispBattleShopLButtonWeapon(void);
extern void menu_sDispBattleShopLButtonOption(void);
extern void menu_sDispBattleShopLButtonSubParts(void);

void menu_sDispBattleShopLButtonZoidWepOptSub(void)
{
    s16 mode = menumode;

    if (mode == 0)
        return;
    if (mode == 2)
        goto display;
    if (mode != 3)
        return;
display:
    menu_sDispBattleShopLButtonZoid();
    menu_sDispBattleShopLButtonWeapon();
    menu_sDispBattleShopLButtonOption();
    menu_sDispBattleShopLButtonSubParts();
}
