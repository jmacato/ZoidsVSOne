#include "zoid.h"

extern void sWeaponUnMount(ZoidState *zoid, s32 slot);

void sWeaponUnMountAll(ZoidState *zoid)
{
    s32 slot;

    if (zoid != 0 && zoid->joint != 0) {
        for (slot = 0; slot < 30; slot++) {
            sWeaponUnMount(zoid, slot);
        }
    }
}
