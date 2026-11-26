#include "zoid.h"
#include "missile.h"

extern f64 __frsqrte(f64);
extern void sMissileSet(ZoidState *owner, ZoidState *target_zoid, Missile *target_missile, f32 matrix[3][4], s32 bullet, s32 extra_damage);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

void sMissileFire(ZoidState *owner, ZoidState *target_zoid, Missile *target_missile, f32 matrix[3][4], s32 bullet, s32 extra_damage)
{
    f32 copy[3][4];
    s32 i;
    s32 j;
    f32 length;
    volatile f32 root;
    s32 pad_stack[1];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            copy[i][j] = matrix[i][j];
    }
    length = sqrtf(matrix[1][0] * matrix[1][0] + matrix[0][0] * matrix[0][0] + matrix[2][0] * matrix[2][0], &root);
    for (i = 0; i < 3; i++)
        copy[i][0] = matrix[i][0] / length;
    sMissileSet(owner, target_zoid, target_missile, copy, bullet, extra_damage);
}
