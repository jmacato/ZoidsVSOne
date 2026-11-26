#include "zoid.h"

extern f64 __frsqrte(f64);
extern f32 sLenPoint3dR(f32 *vector);

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

void ZoidSpdA(ZoidState *zoid)
{
    f32 sum;
    f32 value;
    f32 length;
    f64 scale;
    s32 i;

    sum = 0.0f;
    for (i = 0; i < 3; i++) {
        zoid->previous_displacement[i] = zoid->displacement[i];
        zoid->displacement[i] = zoid->position[i] - zoid->previous_position[i];
        value = zoid->displacement[i];
        sum = value * value + sum;
        zoid->displacement_change[i] = value - zoid->previous_displacement[i];
    }
    zoid->speed = sqrtf(sum);
    length = sLenPoint3dR(zoid->displacement);
    if (length > 1.1) {
        scale = 1.1 / length;
        for (i = 0; i < 3; i++) {
            zoid->displacement[i] *= scale;
        }
    }
}
