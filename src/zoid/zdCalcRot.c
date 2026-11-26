#include "zoid.h"
#include "angle.h"

extern void angLimit(f32 *angle);
extern f32 atan2f(f32 y, f32 x);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

static inline void PAD_STACK(void)
{
    s32 frame_padding[1];
    frame_padding[0] = 0;
}

void zdCalcRot(ZoidState *zoid)
{
    f32 step;
    s32 pb[2];
    f32 diff;
    f32 relative;
    s32 pc[1];
    f32 relativeAbs;
    f32 turn;
    f32 turnAbs;
    ZoidState *target;
    f32 dx;
    f32 dz;
    s32 walk;
    s32 turn_right;
    s32 turn_left;
    s32 fast = 0;
    s32 ok;

    if (zoid != 0 && zoid->joint != 0 && zoid->jump_phase == 0 && zoid->action == ZOID_ACTION_WALK) {
        PAD_STACK();
        walk = zoid->current_animation;
        if (walk == 2) {
            walk = 1;
        }
        step = zoid->step_heading;
        turn_right = 0;
        turn_left = 0;
        diff = step - zoid->heading;
        angLimit(&diff);
        angLimit(&zoid->stick_angle);
        if (!(diff < -DEG2RAD_D(160)) && !(diff > DEG2RAD_D(160))) {
            if (diff < -DEG2RAD_D(100)) {
                turn_right = 1;
            }
            if (diff > DEG2RAD_D(100)) {
                turn_left = 1;
            }
        }
        if (zoid->ai->mode != AI_MODE_NONE) {
            ok = 1;
        } else {
            ok = 1;
        }
        turnAbs = absf(zoid->stick_angle);
        turn = zoid->stick_length;
        if (absf(turn) > 0.2) {
            fast = 1;
        }
        if (zoid->current_animation == 4 && zoid->field_1A80 - zoid->field_1A74 > 0.1 && zoid->field_1A80 > 0.0f) {
            zoid->requested_action = ZOID_ACTION_STOP;
            zoid->action_phase = 0;
            return;
        }
        if (walk == 1 && zoid->field_1A74 - zoid->field_1A80 > 0.005 && zoid->field_1A74 > 0.0f) {
            zoid->requested_action = ZOID_ACTION_DASH;
            zoid->action_phase = 0;
            return;
        }
        if (zoid->target_pending != 0) {
            target = &Zoid[zoid->target_slot];
            if (zoid->ai->mode == AI_MODE_TARGET) {
                target = &Zoid[zoid->ai->field_70];
            }
            dz = target->position[2] - zoid->position[2];
            dx = target->position[0] - zoid->position[0];
            relative = (zoid->target_heading = atan2f(dx, dz)) - zoid->heading;
            angLimit(&relative);
            relativeAbs = absf(relative);
        }
        if (zoid->target_pending == 0) {
            if (zoid->current_animation < 4 && ok != 0 && 0.0f == zoid->field_1A74) {
                if (turn_right != 0) {
                    if (fast != 0) {
                        zoid->requested_action = ZOID_ACTION_TURN_R0;
                        zoid->steer = 0.0f;
                    }
                    return;
                }
                if (turn_left != 0) {
                    if (fast != 0) {
                        zoid->requested_action = ZOID_ACTION_TURN_L0;
                        zoid->steer = 0.0f;
                    }
                    return;
                }
            }
        } else {
            if (0.0f == zoid->field_1A74 && 0.0f == zoid->field_1A80 && 0.0f == zoid->ramped_speed &&
                zoid->ai->mode == AI_MODE_NONE && zoid->field_1BA4 != 2) {
                if (relative > DEG2RAD_D(90)) {
                    zoid->requested_action = ZOID_ACTION_TURN_L1;
                    return;
                }
                if (relative < -DEG2RAD_D(90)) {
                    zoid->requested_action = ZOID_ACTION_TURN_R1;
                    return;
                }
            }
            if (zoid->field_1BA4 == 0 && turnAbs > DEG2RAD_D(120) && fast != 0) {
                if (zoid->field_1A74 > 0.2) {
                    zoid->requested_action = ZOID_ACTION_STOP;
                    zoid->action_phase = 0;
                    return;
                }
                if (absf(diff) > DEG2RAD_D(90)) {
                    turn = -turn;
                    diff += 3.1415926;
                    angLimit(&diff);
                    step += 3.1415926;
                    angLimit(&step);
                    zoid->step_heading = step;
                }
            }
        }
        if (ok == 0) {
            turn = 0.0f;
        }
        if (diff < 0.0f) {
            if (diff < -DEG2RAD_D(2)) {
                zoid->steer = diff;
            } else {
                zoid->steer = 0.0f;
            }
        } else if (diff > DEG2RAD_D(2)) {
            zoid->steer = diff;
        } else {
            zoid->steer = 0.0f;
        }
        if (turn < 0.0f) {
            zoid->steer = -zoid->steer;
        }
        zoid->field_1A74 = turn;
    }
}
