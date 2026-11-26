#include "zoid_ai.h"

s32 zdAI_AngZoidME(s32 index)
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
    degrees = 180.0 * zoid->target_angles[target_index] / 3.1415926;
    return (s32)degrees;
}
