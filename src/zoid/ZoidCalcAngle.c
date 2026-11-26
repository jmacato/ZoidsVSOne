#include "zoid.h"

extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);

f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point)
{
    f32 difference[3];
    f32 angle;

    if (zoid == 0) {
        return 100.0f;
    }
    if (zoid->joint == 0) {
        return 100.0f;
    }
    difference[0] = point->x - zoid->position[0];
    difference[2] = point->z - zoid->position[2];
    if (difference[0] == 0.0f && difference[2] == 0.0f) {
        return 100.0f;
    }
    angle = atan2f(difference[0], difference[2]) - zoid->heading;
    angLimit(&angle);
    return angle;
}
