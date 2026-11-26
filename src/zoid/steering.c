#include "zoid.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern f32 sinf(f32 angle);
extern void angLimit(f32 *angle);

void zdVaSet(ZoidState *zoid)
{
    ZoidControlData *control;
    f32 speed;
    f32 target;
    f32 current;
    f32 difference;
    f32 direction;
    f32 speed_limit = 1.0f;
    f32 step = 2.0 * 3.1415926 * 2.0 / 360.0;

    if (zoid != 0 && zoid->joint != 0) {
        speed = zoid->stick_length;
        control = zoid->control;
        if (speed > speed_limit)
            speed = speed_limit;
        difference = zoid->step_heading - zoid->heading;
        direction = sinf(difference);
        target = speed * direction;
        angLimit(&target);
        if (target < DEG((f32)-control->max_senter_roll))
            target = DEG((f32)-control->max_senter_roll);
        if (target > DEG((f32)control->max_senter_roll))
            target = DEG((f32)control->max_senter_roll);
        current = zoid->senter_roll;
        if (target > current) {
            current += step;
            if (target < current)
                current = target;
        }
        if (target < current) {
            current -= step;
            if (target > current)
                current = target;
        }
        zoid->senter_roll = current;
    }
}
