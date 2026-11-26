#include "weapon.h"

s32 sWeaponStopF(s32 index)
{
    WeaponState *weapon;

    if (index < 0) {
        return 1;
    }
    if (index >= 100) {
        return 1;
    }
    weapon = &sWeapon[index];
    if (weapon->active == 0) {
        return 1;
    }
    return weapon->state_flags & WEAPON_STATE_STOPPED;
}
