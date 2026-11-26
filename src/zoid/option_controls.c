#include "zoid.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);
extern void sWeaponLoopOFF(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);

static void zdWeaponForceFire1_(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount = &zoid->weapon_mounts[selected];
    WeaponSlot *slot;
    s32 index;

    if (mount->active != 0 && zoid->super_attack_input == 0) {
        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0 && mount->entries[index].slot != -1) {
                if (zoid->death_started != 0) {
                    sWeaponLoopOFF(zoid->weapon_slots[mount->entries[index].slot].weapon);
                } else {
                    slot = &zoid->weapon_slots[mount->entries[index].slot];
                    if (sWeaponGetAnim(slot->weapon) != 2) {
                        sWeaponSetAnim(slot->weapon, 2);
                    }
                    sWeaponLoopOFF(slot->weapon);
                    sWeaponStopOFF(slot->weapon);
                }
            }
        }
    }
}

void zdOptionUse4(ZoidState *zoid)
{
    zdWeaponForceFire1_(zoid, WEAPON_MOUNT_SMOKE_MINE);
}

void zdOptionUse5(ZoidState *zoid)
{
    zdWeaponForceFire1_(zoid, WEAPON_MOUNT_SMOKE_MINE);
}
