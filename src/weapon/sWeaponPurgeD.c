#include "weapon.h"

extern void sWeaponPurge(s32 index);

void sWeaponPurgeD(ModelArchive *archive)
{
    WeaponState *weapon;
    s32 index;

    for (index = 0; index < 100; index++) {
        weapon = &sWeapon[index];
        if (weapon->active != 0 && weapon->model != 0 && weapon->archive == archive) {
            sWeaponPurge(index);
        }
    }
}
