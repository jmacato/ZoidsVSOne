#include "zoid.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);
extern void sWeaponLoopOFF(s32 weapon);
extern void sWeaponLoopON(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);

void zdWeaponFireOFF_(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount = &zoid->weapon_mounts[selected];
    WeaponSlot *slot;
    s32 index;

    if (mount->active != 0) {
        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0 && mount->entries[index].slot != -1) {
                slot = &zoid->weapon_slots[mount->entries[index].slot];
                if (sWeaponGetAnim(slot->weapon) == 2) {
                    sWeaponLoopOFF(slot->weapon);
                }
            }
        }
    }
}
