#include "zoid.h"

extern f32 sLenPoint3d(Vec3 *a, Vec3 *b);
extern f32 zdColPosY(Vec3 *point, s32 mode);
extern f32 atan2f(f32 y, f32 x);

f32 zdGoYA3d(ZoidState *zoid, Vec3 *target)
{
    Vec3 from;
    Vec3 to;
    f32 length;
    s32 frame_padding[5];

    if (zoid == 0)
        return 0.0f;
    if (zoid->joint == 0)
        return 0.0f;
    from.x = zoid->position[0];
    to.x = target->x;
    from.y = zoid->position[1];
    to.y = target->y;
    from.z = zoid->position[2];
    to.z = target->z;
    from.y = zoid->ground_height;
    to.y = zoid->ground_height;
    length = sLenPoint3d(&from, &to);
    if (0.0f == length)
        return 0.0f;
    to.y += 150.0f;
    to.y = zdColPosY(&to, 0);
    return atan2f(to.y - from.y, length);
}
