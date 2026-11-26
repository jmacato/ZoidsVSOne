#include "zoid.h"

extern f64 __frsqrte(f64);
extern s32 sChkCubeInCube(f32 matrix[3][4], f32 inverse[3][4]);
extern void PSMTXInverse(f32 src[3][4], f32 inv[3][4]);
extern void sGlobal2Local(HSD_JObj *joint);

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

s32 ZoidCoObjCoObj(CoObj *a, CoObj *b, s32 flags)
{
    f32 pa[3];
    f32 pb[3];
    s32 pad[3];
    f32 d[3];
    f32 s[3];
    f32 sum;
    f32 *dp = d;
    f32 len;
    s32 i;
    s32 k;

    if (a == 0)
        return 0;
    if (b == 0)
        return 0;
    if (a->joint == 0)
        return 0;
    if (b->joint == 0)
        return 0;
    if (sChkCubeInCube(a->joint->matrix, b->inverse) == 0 && sChkCubeInCube(b->joint->matrix, a->inverse) == 0)
        return 0;
    if (a->base_joint == 0)
        return 1;
    if (b->base_joint == 0)
        return 1;
    sum = 0.0f;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < 1; i++) {
            pa[k] = a->joint->matrix[k][3];
            pb[k] = b->joint->matrix[k][3];
        }
        d[k] = pb[k] - pa[k];
        sum += d[k] * d[k];
        dp++;
    }
    len = sqrtf(sum) / 0.02;
    if (0.0f == len)
        return 1;
    if (flags == 0)
        return 1;
    a->object_contact |= 1;
    b->object_contact |= 1;
    for (i = 1; i < 20; i++) {
        for (k = 0; k < 3; k++) {
            s[k] = (d[k] / len) * i;
            a->joint->matrix[k][3] = pa[k] - s[k];
            b->joint->matrix[k][3] = pb[k] + s[k];
        }
        PSMTXInverse(a->joint->matrix, a->inverse);
        PSMTXInverse(b->joint->matrix, b->inverse);
        if (sChkCubeInCube(a->joint->matrix, b->inverse) == 0 && sChkCubeInCube(b->joint->matrix, a->inverse) == 0)
            break;
    }
    a->base_joint->matrix[0][3] -= s[0];
    b->base_joint->matrix[0][3] += s[0];
    a->base_joint->matrix[1][3] -= s[1];
    b->base_joint->matrix[1][3] += s[1];
    a->base_joint->matrix[2][3] -= s[2];
    b->base_joint->matrix[2][3] += s[2];
    sGlobal2Local(a->base_joint);
    sGlobal2Local(b->base_joint);
    return 1;
}
