#include "zoid.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);
extern void sWeaponLoopOFF(s32 weapon);
extern void sWeaponLoopON(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);

void zdWeaponFireON_(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount = &zoid->weapon_mounts[selected];
    WeaponSlot *slot;
    s32 index;
    s32 animation;

    if (mount->active != 0) {
        zoid->anim1_frames = 0;
        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0 && mount->entries[index].slot != -1) {
                if (zoid->death_started != 0) {
                    sWeaponLoopOFF(zoid->weapon_slots[mount->entries[index].slot].weapon);
                } else {
                    slot = &zoid->weapon_slots[mount->entries[index].slot];
                    animation = sWeaponGetAnim(slot->weapon);
                    if (animation == 2) {
                        sWeaponLoopON(slot->weapon);
                        sWeaponStopOFF(slot->weapon);
                    }
                    if (animation == 1) {
                        sWeaponSetAnim(slot->weapon, 2);
                        sWeaponLoopON(slot->weapon);
                        sWeaponStopOFF(slot->weapon);
                    }
                }
            }
        }
    }
}
