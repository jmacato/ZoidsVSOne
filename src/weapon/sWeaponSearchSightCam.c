#include "weapon.h"
#include "zoid.h"
#include "missile.h"

extern s32 sWpSearchSight1z(WeaponState *weapon, ZoidState *zoid, ZoidState *target);

void sWeaponSearchSightCam(WeaponState *weapon, ZoidState *zoid)
{
    s32 i;
    ZoidState *target;
    Missile *missile;
    s32 slot = zoid->slot;

    if (zoid->target_pending != 0) {
        if (sWpSearchSight1z(weapon, zoid, &Zoid[zoid->target_slot]) != 0)
            return;
    }
    for (i = 0; i < 16; i++) {
        target = &Zoid[i];
        if (target != zoid && target->joint != 0 && target->death_started == 0 && slot != target->slot) {
            if (sWpSearchSight1z(weapon, zoid, target) != 0)
                return;
        }
    }
    for (i = 0, missile = missileStart; i < 200; i++, missile++) {
        if (missile == 0)
            break;
    }
}
