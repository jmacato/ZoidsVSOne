#include "weapon.h"

extern s32 getEndF(HSD_JObj *joint);

s32 sWeaponEndF(s32 index)
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
    if ((weapon->state_flags & WEAPON_STATE_STOPPED) != 0) {
        return 1;
    }
    return getEndF(weapon->archive->models[weapon->model]);
}
