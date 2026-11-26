#include "zoid.h"

extern s32 sWeaponEndF(s32 weapon);
extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);
extern void sWeaponLoopON(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);

s32 zdWeaponWpOFF(ZoidState *zoid, WeaponMount *mount)
{
    WeaponMountEntry *entry;
    s32 count;
    s32 i;
    s32 weapon;
    s32 animation;
    s32 slot;
    WeaponSlot *weaponSlot;

    if (mount->active == 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        entry = &mount->entries[i];
        if (entry->active == 0) {
            continue;
        }
        if (entry->slot == -1) {
            entry->active = 0;
            continue;
        }
        slot = entry->slot;
        weaponSlot = &zoid->weapon_slots[slot];
        weapon = weaponSlot->weapon;
        if (weapon == -1) {
            continue;
        }
        sWeaponStopOFF(weapon);
        if (sWeaponGetAnim(weapon) == 4) {
            continue;
        }
        sWeaponLoopON(weapon);
        if (sWeaponEndF(weapon) != 0) {
            animation = sWeaponGetAnim(weapon);
            if (animation == 4) {
                continue;
            }
            if (animation == 3) {
                animation = 4;
            } else {
                animation = 3;
            }
            sWeaponSetAnim(weapon, animation);
        }
        count++;
    }
    return count;
}
