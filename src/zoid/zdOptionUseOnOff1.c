#include "zoid.h"

extern void zdWeaponForceFireOnOff_(ZoidState *zoid, s32 mount, s32 on);

void zdOptionUseOnOff1(ZoidState *zoid, s32 on)
{
    zdWeaponForceFireOnOff_(zoid, WEAPON_MOUNT_SHIELD, on);
}
