#include "zoid.h"

extern void angLimit(f32 *angle);
extern void ZoidCopyAnim(ZoidState *zoid);
extern void ZoidAnim(ZoidState *zoid);

void ZoidAllAnim(void)
{
    s32 actor;

    for (actor = 0; actor < 16; actor++) {
        ZoidState *zoid = &Zoid[actor];
        if (zoid->joint != 0) {
            angLimit(&zoid->heading);
            ZoidCopyAnim(zoid);
            ZoidAnim(zoid);
        }
    }
}
