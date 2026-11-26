#include "weapon.h"

extern void sWeaponMove(WeaponState *weapon);

void sWeaponMoveAll(void)
{
    WeaponState *weapon;
    s32 index;

    for (index = 0; index < 100; index++) {
        weapon = &sWeapon[index];
        if (weapon->active != 0) {
            sWeaponMove(weapon);
        }
    }
}
