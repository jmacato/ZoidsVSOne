#include "zoid.h"
#include "game_camera.h"
#include "game_mode.h"
#include "ground_collision.h"

extern f32 cosf(f32);
extern f32 sinf(f32);

static inline f64 fabs(f64 x)
{
    return __fabs(x);
}

static inline f32 fabsf(f32 value)
{
    return (*(u32 *)&value &= 0x7FFFFFFF, value);
}

void camR_jobj(CameraRange *range, HSD_JObj *joint)
{
    f32 c;
    f32 s;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 side;
    f32 front;
    f32 size;
    f32 limit;
    f32 pad[1];

    if (joint == 0)
        return;
    c = cosf(range->heading);
    s = range->heading;
    s = sinf(s);
    dz = joint->matrix[2][3] - range->origin.z;
    dx = joint->matrix[0][3] - range->origin.x;
    dy = joint->matrix[1][3] - range->origin.y;
    side = -dx * c + dz * s;
    front = dx * s + dz * c;
    size = 1.5 * fabsf(side);
    size = (f32)size + fabsf(front);
    limit = fabsf(front);
    limit = limit + fabs(1.5 * dy);
    if (size < limit)
        size = limit;
    if (range->radius < size)
        range->radius = size;
}
