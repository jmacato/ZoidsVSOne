#include "types.h"

extern s16 menumode;
extern void menu_sDispBattleSetLButtonZoid(void);
extern void menu_sDispBattleSetLButtonWeapon(void);
extern void menu_sDispBattleSetLButtonOption(void);
extern void menu_sDispBattleSetLButtonSubParts(void);
extern void menu_sDispBattleSetLButtonReset(void);
extern void menu_sDispBattleSetLButtonExit(void);
extern void menu_sDispBattleSetZoidStatus(void);

void menu_sDispBattleSetLButton(void)
{
    if (menumode != 0) {
        menu_sDispBattleSetLButtonZoid();
        menu_sDispBattleSetLButtonWeapon();
        menu_sDispBattleSetLButtonOption();
        menu_sDispBattleSetLButtonSubParts();
        menu_sDispBattleSetLButtonReset();
        menu_sDispBattleSetLButtonExit();
        menu_sDispBattleSetZoidStatus();
    }
}
