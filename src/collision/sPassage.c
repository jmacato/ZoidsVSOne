#include "types.h"

extern f64 __frsqrte(f64);
extern void sPtRotX(Vec3 *point, f32 cosine, f32 sine);
extern void sPtRotY(Vec3 *point, f32 cosine, f32 sine);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

/* distance from point to the line start-end, 10000.0f when point projects outside the segment */
f32 sPassage(Vec3 *start, Vec3 *end, Vec3 *point)
{
    Vec3 to_point;
    Vec3 to_end;
    s32 pad0;
    s32 pad1;
    volatile f32 r1;
    volatile f32 r2;
    volatile f32 r3;
    s32 unused[1];
    f32 x;
    f32 y;
    f32 z;
    f32 len;

    to_end.x = end->x - start->x;
    to_point.x = point->x - start->x;
    to_end.y = end->y - start->y;
    to_point.y = point->y - start->y;
    to_end.z = end->z - start->z;
    to_point.z = point->z - start->z;
    x = to_end.x;
    z = to_end.z;
    len = sqrtf(x * x + z * z, &r1);
    if (len != 0.0f) {
        x = -(x / len);
        z = z / len;
        sPtRotY(&to_end, z, x);
        sPtRotY(&to_point, z, x);
    }
    x = to_end.y;
    z = to_end.z;
    len = sqrtf(x * x + z * z, &r2);
    if (len != 0.0f) {
        x = x / len;
        z = z / len;
        sPtRotX(&to_end, z, -x);
        sPtRotX(&to_point, z, -x);
    }
    z = to_point.z;
    x = to_point.x;
    y = to_point.y;
    if (z < 0.0f)
        return 10000.0f;
    if (z > to_end.z)
        return 10000.0f;
    return sqrtf(x * x + y * y, &r3);
}
