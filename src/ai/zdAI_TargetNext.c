#include "zoid_ai.h"

extern void ZoidSearchNextTarget(ZoidState *zoid);

void zdAI_TargetNext(s32 index)
{
    ZoidState *zoid;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            ZoidSearchNextTarget(zoid);
        }
    }
}
