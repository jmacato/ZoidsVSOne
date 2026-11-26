#include "zoid.h"

void ZoidSearchNextTarget(ZoidState *zoid)
{
    ZoidState *target;
    s32 index;
    s32 team;
    s32 i;

    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    if (zoid->death_started == 0) {
        team = zoid->slot;
        index = zoid->target_slot;
        for (i = 0; i < 16; i++) {
            index++;
            if (index >= 16)
                index = 0;
            if (index < 0)
                index = 15;
            target = &Zoid[index];
            if (target != 0 && target->joint != 0 && team != target->slot && target->death_started == 0 &&
                target->stel_state != ZOID_STEL_ON && zoid->target_visibility[index] != 0) {
                zoid->target_slot = index;
                zoid->target_pending = 1;
                return;
            }
        }
        zoid->target_pending = 0;
    }
}
