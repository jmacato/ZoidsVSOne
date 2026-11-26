#include "zoid.h"
#include "angle.h"

extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void zdStep0f(ZoidState *zoid, f32 angle)
{
    s32 busy;
    s32 request;
    s32 action;
    f32 heading;
    f32 magnitude;

    if (zoid != 0 && zoid->joint != 0) {
        action = zoid->action;
        if (action != ZOID_ACTION_DEAD && action != ZOID_ACTION_DEATH) {
            busy = 0;
            request = zoid->requested_action;
            if (request == ZOID_ACTION_STEP_0) busy = 1;
            if (request == ZOID_ACTION_STEP_1) busy = 1;
            if (request == ZOID_ACTION_STEP_2) busy = 1;
            if (request == ZOID_ACTION_STEP_3) busy = 1;
            if (request == ZOID_ACTION_STEP_REQUEST_0) busy = 1;
            if (request == ZOID_ACTION_STEP_REQUEST_1) busy = 1;
            if (request == ZOID_ACTION_STEP_REQUEST_2) busy = 1;
            if (request == ZOID_ACTION_STEP_REQUEST_3) busy = 1;
            if (action == ZOID_ACTION_STEP_0) busy = 1;
            if (action == ZOID_ACTION_STEP_1) busy = 1;
            if (action == ZOID_ACTION_STEP_2) busy = 1;
            if (action == ZOID_ACTION_STEP_3) busy = 1;
            if (action == ZOID_ACTION_STEP_REQUEST_0) busy = 1;
            if (action == ZOID_ACTION_STEP_REQUEST_1) busy = 1;
            if (action == ZOID_ACTION_STEP_REQUEST_2) busy = 1;
            if (action == ZOID_ACTION_STEP_REQUEST_3) busy = 1;
            if (busy != 0) {
                zoid->requested_action = 0;
            } else {
                angLimit(&angle);
                heading = zoid->heading + angle;
                zoid->launch_velocity.x = 0.8 * zoid->displacement[0] + sinf(heading);
                zoid->launch_velocity.z = 0.8 * zoid->displacement[2] + cosf(heading);
                magnitude = absf(angle);
                zoid->requested_action = ZOID_ACTION_STEP_REQUEST_0;
                if (magnitude < DEG2RAD_D(45)) {
                    zoid->requested_action = ZOID_ACTION_STEP_REQUEST_0;
                } else if (magnitude > DEG2RAD_D(135)) {
                    zoid->requested_action = ZOID_ACTION_STEP_REQUEST_1;
                } else if (angle > 0.0f) {
                    zoid->requested_action = ZOID_ACTION_STEP_REQUEST_3;
                } else {
                    zoid->requested_action = ZOID_ACTION_STEP_REQUEST_2;
                }
            }
        }
    }
}
