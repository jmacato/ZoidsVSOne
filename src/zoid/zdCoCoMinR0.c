#include "zoid.h"

extern f64 __frsqrte(f64);

static inline f32 sqrtf(f32 x)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;
    volatile f32 y;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

static inline f32 zdCoSub(f32 a, f32 b)
{
    Vec3 t;

    t.x = a - b;
    return t.x;
}

f32 zdCoCoMinR0(CoObj *a, CoObj *b, Vec3 *direction)
{
    HSD_JObj *ja;
    HSD_JObj *jb;
    f32 sum;
    f32 distance;
    f32 radius;
    f32 delta;

    if (a == 0) {
        return 0.0f;
    }
    if (b == 0) {
        return 0.0f;
    }
    ja = a->joint;
    jb = b->joint;
    if (ja == 0) {
        return 0.0f;
    }
    if (jb == 0) {
        return 0.0f;
    }
    sum = 0.0f;
    delta = ja->matrix[0][3] - jb->matrix[0][3];
    direction->x = delta;
    sum += delta * delta;
    delta = ja->matrix[1][3] - jb->matrix[1][3];
    direction->y = delta;
    sum += delta * delta;
    delta = ja->matrix[2][3] - jb->matrix[2][3];
    direction->z = delta;
    sum += delta * delta;
    distance = sqrtf(sum);
    if (0.0f == distance) {
        return 0.0f;
    }
    direction->x /= distance;
    direction->y /= distance;
    direction->z /= distance;
    radius = a->minimum_scale + b->minimum_scale;
    if (distance >= radius) {
        return 0.0f;
    }
    return zdCoSub(radius, distance);
}
