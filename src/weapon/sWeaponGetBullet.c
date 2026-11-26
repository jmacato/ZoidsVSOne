#include "weapon.h"

s32 sWeaponGetBullet(s32 index)
{
    WeaponState *weapon;

    if (index < 0) {
        return 0;
    }
    if (index >= 100) {
        return 0;
    }
    weapon = &sWeapon[index];
    if (weapon->active == 0) {
        return 0;
    }
    return weapon->ammo;
}
