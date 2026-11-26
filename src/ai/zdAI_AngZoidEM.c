#include "zoid_ai.h"

s32 zdAI_AngZoidEM(s32 index)
{
    ZoidState *zoid;
    ZoidState *target;
    s32 target_index;
    f32 degrees;

    if (index < 0) {
        return -1;
    }
    if (index >= 16) {
        return -1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return -1;
    }
    target_index = zoid->target_slot;
    if (target_index < 0) {
        return -1;
    }
    if (target_index >= 16) {
        return -1;
    }
    target = &Zoid[target_index];
    if (target->joint == 0) {
        return -1;
    }
    {
        f32 angle = target->target_angles[index];

        degrees = 180.0 * angle / 3.1415926;
        return (s32)degrees;
    }
}
