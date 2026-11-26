#include "missile.h"

static void *missileFile[130];
Missile missileStart[200];
extern void ZeroMemory(void *dst, u32 size);
extern void *sMissileLoad(char *name);

void sMissilePrologue(void)
{
    s32 i;
    ZeroMemory(missileStart, sizeof(missileStart));
    ZeroMemory(missileFile, sizeof(missileFile));
    for (i = 0; i < 130; i++) {
        missileFile[i] = sMissileLoad(Tea_bulletdat[i].name);
    }
}
