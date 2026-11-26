#pragma readonly_strings on
#include "zoid.h"

extern void OSReport(const char *format, ...);
extern s32 sWeaponSet(s32 part, ZoidState *zoid, s32 slot, WeaponMount *mount);

void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount)
{
    OSReport("mount wp    zoid=%d mt=%d act=%d wp=%d\n", zoid ? zoid->type : -1, slot, mount, part);
    if (zoid != 0 && zoid->joint != 0 && part > 0) {
        WeaponMount *entry = &zoid->weapon_mounts[mount];

        if (sWeaponSet(part, zoid, slot, entry) != -1)
            zoid->mount_has_weapon[mount] = 1;
    }
}
