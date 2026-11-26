#include "weapon.h"
#include "zoid.h"

extern void zdCalcWeaponS(ZoidState *zoid, s32 part);

void zdCalcWeapon(ZoidState *zoid, s32 weapon)
{
    if (zoid != 0 && zoid->joint != 0 && weapon >= 0 && sWeapon[weapon].active != 0)
        zdCalcWeaponS(zoid, sWeapon[weapon].type);
}
