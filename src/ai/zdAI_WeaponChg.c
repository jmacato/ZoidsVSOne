#include "zoid_ai.h"

extern void zdWeaponChg(ZoidState *zoid);

void zdAI_WeaponChg(s32 index)
{
    if (index >= 0 && index < 16) {
        zdWeaponChg(&Zoid[index]);
    }
}
