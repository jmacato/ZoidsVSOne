#include "zoid.h"

extern void zdWeaponFireOFF_(ZoidState *zoid, s32 mount);

void zdWeaponFireOFF(ZoidState *zoid)
{
    WeaponMount *mount;
    s32 state;
    s32 index;

    if (zoid != 0 && zoid->joint != 0) {
        if (zoid->weapon_mount == -1) {
            return;
        }
        mount = &zoid->weapon_mounts[zoid->weapon_mount];
        if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK) {
            return;
        }
        if (zoid->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK) {
            return;
        }
        if (mount->active == 0) {
            return;
        }
        state = mount->state;
        if (state == 3) {
            mount->state = 6;
        }
        if (state == 5) {
            mount->state = 6;
        }
        if (zoid->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
            for (index = 0; index < 10; index++) {
                zdWeaponFireOFF_(zoid, index);
            }
        } else {
            zdWeaponFireOFF_(zoid, zoid->weapon_mount);
        }
    }
}
