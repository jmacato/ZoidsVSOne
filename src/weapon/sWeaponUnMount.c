#include "zoid.h"

extern void sWeaponPurge(s32 index);

void sWeaponUnMount(ZoidState *zoid, s32 slot)
{
    if (zoid != 0 && zoid->joint != 0 && slot >= 0 && slot < 30) {
        sWeaponPurge(zoid->weapon_slots[slot].weapon);
    }
}
