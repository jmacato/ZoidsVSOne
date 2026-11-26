#include "weapon.h"

void sWeaponStopOFF(s32 index)
{
    WeaponState *weapon;

    if (index >= 0 && index < 100) {
        weapon = &sWeapon[index];
        if (weapon->active != 0) {
            weapon->state_flags &= ~WEAPON_STATE_STOPPED;
        }
    }
}
