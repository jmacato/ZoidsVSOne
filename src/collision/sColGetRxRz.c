#include "ground_collision.h"

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);

void sColGetRxRz(Vec3 *normal, f32 heading, f32 *rx, f32 *rz)
{
    f32 x;
    f32 z;
    f32 side;
    f32 y;
    f32 sine;
    f32 cosine;
    f32 forward;
    f32 sine2;
    f32 cosine2;
    f32 nx;

    x = -normal->x;
    z = normal->z;
    y = normal->y;

    sine = sinf(heading);
    cosine = cosf(heading);
    side = x * cosine + z * sine;
    cosine2 = cosf(heading);
    sine2 = sinf(heading);
    nx = -x;
    forward = nx * sine2 + z * cosine2;
    *rz = atan2f(side, y);
    *rx = atan2f(forward, y);
}
