#include "zoid.h"

extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern f32 zdColPosY(f32 *point, s32 flags);

f32 zdGoY(ZoidState *zoid, f32 angle, f32 distance)
{
    f32 origin[3];
    f32 target[3];
    /* MWCC retains this unused slot in the original point-buffer layout. */
    f64 frame_padding;
    s32 axis;

    if (zoid == 0) {
        return 0.0f;
    }
    if (zoid->joint == 0) {
        return 0.0f;
    }
    for (axis = 0; axis < 3; axis++) {
        target[axis] = origin[axis] = zoid->position[axis];
    }
    target[1] = origin[1] = zoid->ground_height;
    target[0] += distance * sinf(angle + zoid->heading);
    target[2] += distance * cosf(angle + zoid->heading);
    target[1] = zdColPosY(target, 0);
    return target[1] - origin[1];
}
