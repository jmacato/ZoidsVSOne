#include "zoid_ai.h"

extern void zdWeaponFireON(ZoidState *zoid);

void zdAI_WeaponFireON(s32 index)
{
    if (index >= 0 && index < 16) {
        zdWeaponFireON(&Zoid[index]);
    }
}
