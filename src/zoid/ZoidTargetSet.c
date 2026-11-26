#include "zoid.h"

void ZoidTargetSet(ZoidState *zoid, s32 index)
{
    ZoidState *target;

    if (zoid != 0 && zoid->joint != 0 && index >= 0 && index < 16) {
        target = &Zoid[index];
        if (target->joint != 0 && target->stel_state != ZOID_STEL_ON &&
            zoid->target_visibility[index] != 0 &&
            (s32)zoid->slot != (s32)target->slot) {
            zoid->target_slot = index;
            zoid->target_pending = 1;
        }
    }
}
