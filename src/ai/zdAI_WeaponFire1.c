#include "zoid_ai.h"

extern void zdWeaponFire1(ZoidState *zoid);

void zdAI_WeaponFire1(s32 index)
{
    if (index >= 0 && index < 16) {
        zdWeaponFire1(&Zoid[index]);
    }
}
