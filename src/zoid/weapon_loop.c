#include "zoid.h"

extern s32 zdWeaponNow(ZoidState *zoid);
extern void zdWeaponActLoop(ZoidState *zoid);
extern void zdOptionLoop(ZoidState *zoid);
extern void zdSmokeRecv(ZoidState *zoid);

void ZoidWeaponActLoop(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        ZoidState *zoid = &Zoid[i];
        zdWeaponNow(zoid);
        zdWeaponActLoop(zoid);
        zdOptionLoop(zoid);
        zdSmokeRecv(zoid);
    }
}
