#include "types.h"

extern void sWeaponMoveAll(void);
extern void sWeaponDispAll(void);

void menu_sDispBattleFarmWeapon(void)
{
    sWeaponMoveAll();
    sWeaponDispAll();
}
