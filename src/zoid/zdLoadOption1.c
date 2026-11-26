#include "zoid.h"
#include "game_zoid_data.h"
extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);

void zdLoadOption1(ZoidState *zoid, s32 part)
{
    s32 slot = Tea_zoiddat[zoid->type].option_one;

    if (slot <= 27) {
        zoid->option_type = ZOID_OPTION_SHIELD;
        zoid->option_energy_max = 2000;
        zoid->option_energy = 0;
        zoid->option_start_cost = 500;
        zoid->option_hold_cost = 2;
        zoid->option_recharge = 3;
        sWeaponMount(part, zoid, slot, WEAPON_MOUNT_SHIELD);
    }
}
