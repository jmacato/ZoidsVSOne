#include "zoid.h"

extern void angLimit(f32 *angle);

void zdStep1(ZoidState *zoid, s32 degrees)
{
    s32 action;

    if (zoid != 0 && zoid->joint != 0) {
        action = zoid->action;
        if (action != ZOID_ACTION_DEAD && action != ZOID_ACTION_DEATH) {
            zoid->step_heading = (f32)(((2.0 * (3.1415926 * (f64)(f32)degrees)) / 360.0)
                                      + (f64)zoid->heading);
            angLimit(&zoid->step_heading);
            zoid->requested_action = ZOID_ACTION_STEP_0;
        }
    }
}
