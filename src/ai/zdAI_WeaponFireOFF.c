#include "zoid_ai.h"

extern void zdWeaponFireOFF(ZoidState *zoid);

void zdAI_WeaponFireOFF(s32 index)
{
    if (index >= 0 && index < 16) {
        zdWeaponFireOFF(&Zoid[index]);
    }
}
