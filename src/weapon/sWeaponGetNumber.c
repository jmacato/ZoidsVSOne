#include "weapon.h"
#include "zoid.h"

s32 sWeaponGetNumber(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount;
    s32 index;
    s32 weapon;

    if (zoid == 0) {
        return -1;
    }
    if (zoid->joint == 0) {
        return -1;
    }
    if (selected == -1) {
        return -1;
    }
    mount = &zoid->weapon_mounts[selected];
    if (mount->active == 0) {
        return -1;
    }
    for (index = 0; index < 4; index++) {
        if (mount->entries[index].active != 0 && mount->entries[index].slot != -1) {
            weapon = zoid->weapon_slots[mount->entries[index].slot].weapon;
            if (weapon != -1) {
                return sWeapon[weapon].type;
            }
        }
    }
    return -1;
}
