#include "zoid.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern s32 sWeaponEndF(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);
extern void sWeaponLoopOFF(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);

void zdWeaponForceFireOnOff_(ZoidState *zoid, s32 selected, s32 on)
{
    WeaponMount *mount = &zoid->weapon_mounts[selected];
    WeaponSlot *slot;
    s32 index;
    s32 animation;
    s32 next;
    s32 ended;

    if (mount->active != 0 && (on == 0 || zoid->super_attack_input == 0)) {
        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0 && mount->entries[index].slot != -1) {
                if (zoid->death_started != 0) {
                    on = 0;
                } else {
                    slot = &zoid->weapon_slots[mount->entries[index].slot];
                    animation = sWeaponGetAnim(slot->weapon);
                    ended = sWeaponEndF(slot->weapon);
                    next = animation;
                    if (on != 0) {
                        switch (animation) {
                        case 0:
                            if (ended != 0) next = 1;
                            break;
                        case 1:
                            next = 2;
                            break;
                        case 2:
                            break;
                        case 3:
                            if (ended != 0) next = 0;
                            break;
                        case 4:
                            next = 0;
                            break;
                        default:
                            next = 0;
                            break;
                        }
                    } else {
                        switch (animation) {
                        case 0:
                            if (ended != 0) next = 3;
                            break;
                        case 1:
                            next = 3;
                            break;
                        case 2:
                            if (ended != 0) next = 3;
                            break;
                        case 3:
                            if (ended != 0) next = 4;
                            break;
                        case 4:
                            next = 4;
                            break;
                        default:
                            next = 4;
                            break;
                        }
                    }
                    if (animation != next || next == 4)
                        sWeaponSetAnim(slot->weapon, next);
                    sWeaponLoopOFF(slot->weapon);
                    sWeaponStopOFF(slot->weapon);
                }
            }
        }
    }
}
