#include "zoid.h"
#include "weapon.h"
#include "missile.h"

extern void sWeaponSearchSight(WeaponState *weapon);

void zdSearchSight(ZoidState *zoid, s32 index)
{
    WeaponMount *mount;
    WeaponMountEntry *entry;
    s32 i;
    s32 weapon;
    WeaponState *state;
    s32 frame_padding[2];

    if (zoid != 0 && zoid->joint != 0 && index != -1) {
        mount = &zoid->weapon_mounts[index];
        if (mount->active != 0) {
            for (i = 0; i < 4; i++) {
                entry = &mount->entries[i];
                if (entry->active != 0 && entry->slot != -1) {
                    weapon = zoid->weapon_slots[entry->slot].weapon;
                    if (weapon != -1) {
                        state = &sWeapon[weapon];
                        if (state->bullet_kind == BULLET_KIND_AT20) {
                            sWeaponSearchSight(state);
                        }
                    }
                }
            }
        }
    }
}
