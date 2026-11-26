#include "zoid_ai.h"

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

s32 zdAI_Look(s32 index)
{
    ZoidState *zoid;
    ZoidState *target;
    s32 slot;
    f32 angle;

    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return 0;
    }
    if (zoid->target_pending == 0) {
        return 0;
    }
    slot = zoid->target_slot;
    if (slot < 0) {
        return 0;
    }
    if (slot >= 16) {
        return 0;
    }
    target = &Zoid[slot];
    if (target->joint == 0) {
        return 0;
    }
    if (zoid == target) {
        return 0;
    }
    if (0.0f != zoid->stick_length) {
        zoid->stick_length = 0.0f;
        return 0;
    }
    if (zoid->field_1A74 > 0.0f) {
        zoid->field_1A74 -= 0.1;
        if (zoid->field_1A74 < 0.0f) {
            zoid->field_1A74 = 0.0f;
        }
        return 0;
    }
    angle = zoid->target_angles[slot];
    if (absf(angle) < 2.0 * (3.1415926 * 5) / 360.0) {
        return 1;
    }
    if (angle < 0.0f) {
        zoid->requested_action = ZOID_ACTION_TURN_L2;
    } else {
        zoid->requested_action = ZOID_ACTION_TURN_R2;
    }
    return 0;
}
