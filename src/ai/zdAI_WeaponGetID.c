#include "zoid_ai.h"

extern s32 sWeaponGetNumber(ZoidState *zoid, s32 mount);

s32 zdAI_WeaponGetID(s32 index)
{
    ZoidState *zoid;

    if (index < 0) {
        return -1;
    }
    if (index >= 16) {
        return -1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return -1;
    }
    return sWeaponGetNumber(zoid, zoid->weapon_mount);
}
