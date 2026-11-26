#include "zoid_ai.h"

extern s32 sWeaponGetMountBullet(ZoidState *zoid, s32 mount);

s32 zdAI_WeaponBullet(s32 index)
{
    ZoidState *zoid;

    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    return sWeaponGetMountBullet(zoid, zoid->weapon_mount);
}
