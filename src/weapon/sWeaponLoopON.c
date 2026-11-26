#include "weapon.h"

void sWeaponLoopON(s32 index)
{
    WeaponState *weapon;

    if (index >= 0 && index < 100) {
        weapon = &sWeapon[index];
        if (weapon->active != 0) {
            weapon->flags &= ~WEAPON_FLAG_LOOP_OFF;
        }
    }
}
