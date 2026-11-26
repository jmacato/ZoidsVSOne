#include "weapon.h"

void sWeaponSetAnim(s32 index, s32 animation)
{
    WeaponState *weapon;
    s32 anim;
    s32 model;

    if (index < 0) {
        return;
    }
    if (index >= 100) {
        return;
    }
    weapon = &sWeapon[index];
    if (weapon->active == 0) {
        return;
    }
    model = weapon->model;
    if (!weapon->archive->models[model]) {
        return;
    }
    model = weapon->model;
    anim = animation;
    SetAnimArc2(weapon->archive, model, anim);
    weapon->animation = animation;
    weapon->state_flags &= ~WEAPON_STATE_STOPPED;
}
