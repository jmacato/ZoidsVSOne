#include "zoid_ai.h"

extern void zdStep1(ZoidState *zoid, s32 degrees);

void zdAI_Step(s32 index, s32 degrees)
{
    ZoidState *zoid;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            zdStep1(zoid, degrees);
        }
    }
}
