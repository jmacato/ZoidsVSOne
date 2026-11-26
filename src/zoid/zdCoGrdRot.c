#include "zoid.h"

#define NULL 0
#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);

static inline f32 fabsf(f32 *value)
{
    return (*(u32 *)value &= 0x7FFFFFFF, *value);
}

static inline f32 angleY(f32 x, f32 z)
{
    return atan2f(x, z);
}

f32 zdCoGrdRot(ZoidState *zoid, HSD_JObj **joint, f32 *direction, s32 scale)
{
    f32 position[3];
    f32 delta[3];
    f32 next[3];
    s32 pad[3];
    f32 turn;
    f32 diff;
    f32 abs1;
    f32 abs2;
    f32 rate;
    f32 angle;
    s32 i;

    if (joint == NULL)
        return 0.0f;
    if (*joint == NULL)
        return 0.0f;
    for (i = 0; i < 3; i++) {
        position[i] = zoid->position[i];
        delta[i] = (*joint)->matrix[i][3] - position[i];
        next[i] = (f32)scale * direction[i] + delta[i];
    }
    if (0.0f == delta[0] && 0.0f == delta[2])
        return 0.0f;
    if (delta[0] == next[0] && delta[2] == next[2])
        return 0.0f;
    angle = atan2f(delta[0], delta[2]);
    turn = angleY(next[0], next[2]) - angle;
    rate = 0.02f;
    diff = angle - zoid->heading;
    angLimit(&diff);
    abs1 = diff;
    if (fabsf(&abs1) > DEG(30))
        rate = 0.0003f;
    abs2 = diff;
    if (fabsf(&abs2) > DEG(80))
        rate = 0.0007f;
    turn *= rate;
    angLimit(&turn);
    return turn;
}
