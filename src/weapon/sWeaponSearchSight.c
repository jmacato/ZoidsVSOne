#include "weapon.h"
#include "zoid.h"

extern u32 vsyncN;
extern void sWeaponSearchSightCam(WeaponState *weapon, ZoidState *zoid);

void sWeaponSearchSight(WeaponState *weapon)
{
    ZoidState *zoid = weapon->owner;

    if (zoid != 0 && zoid->joint != 0) {
        if ((vsyncN & 31) == zoid->index && zoid->enemy_smoke_timer == 0) {
            sWeaponSearchSightCam(weapon, zoid);
        }
    }
}
