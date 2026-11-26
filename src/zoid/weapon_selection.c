#include "zoid.h"

void zdWeaponChg(ZoidState *zoid)
{
    s32 count;
    s32 part;
    WeaponMount *mount;
    WeaponMountEntry *entry;
    s32 index;

    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    if (zoid->death_started != 0)
        return;
    count = 0;
    for (index = 0; index < 10; index++) {
        mount = &zoid->weapon_mounts[index];
        if (mount->active != 0) {
            for (part = 0; part < 4; part++) {
                entry = &mount->entries[part];
                if (entry->active != 0) {
                    if (entry->slot != -1)
                        break;
                    entry->active = 0;
                }
            }
            if (part == 4)
                mount->active = 0;
            else
                count++;
        }
    }
    zoid->weapon_mount_count = count;
    if (count < 1)
        return;
    if (zoid->weapon_mount_count > 0) {
        for (index = 0; index < 10; index++) {
            zoid->selected_weapon_mount++;
            if (zoid->selected_weapon_mount > 9)
                zoid->selected_weapon_mount = 0;
            if (zoid->weapon_mounts[zoid->selected_weapon_mount].active != 0)
                break;
        }
    }
}
