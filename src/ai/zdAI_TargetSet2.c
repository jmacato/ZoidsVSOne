#include "zoid_ai.h"

extern void ZoidTargetSet(ZoidState *zoid, s32 index);

void zdAI_TargetSet2(s32 index)
{
    ZoidState *zoid;
    s32 target;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            target = zoid->ai->target_index;
            if (target != -1) {
                ZoidTargetSet(zoid, target);
            }
        }
    }
}
