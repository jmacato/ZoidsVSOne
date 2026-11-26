#include "zoid.h"

extern f32 zdCoCoMinR0(CoObj *a, CoObj *b, Vec3 *direction);
extern f32 sLenPoint3dR(Vec3 *point);

f32 zdCoCoMinR(ZoidState *a, ZoidState *b)
{
    f32 distance[5][5];
    CoObj *parts_a[8];
    CoObj *parts_b[8];
    Vec3 direction;
    Vec3 push;
    f32 unused[4];
    f32 *vec;
    s32 i;
    s32 j;
    f32 d;
    f32 max;
    f32 len;
    f32 plus;
    f32 minus;

    vec = &push.x;
    parts_a[0] = &a->hip_coobj;
    parts_b[0] = &b->hip_coobj;
    parts_a[1] = &a->bust_coobj;
    parts_b[1] = &b->bust_coobj;
    parts_a[2] = &a->neck_coobj;
    parts_b[2] = &b->neck_coobj;
    parts_a[3] = &a->r_leg1_coobj;
    parts_b[3] = &b->r_leg1_coobj;
    parts_a[4] = &a->l_leg1_coobj;
    parts_b[4] = &b->l_leg1_coobj;
    for (i = 0; i < 3; i++)
        vec[i] = 0.0f;
    max = -1.0f;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            d = zdCoCoMinR0(parts_a[i], parts_b[j], &direction);
            distance[i][j] = d;
            if (0.0f != d && (max == -1.0f || max < d)) {
                max = d;
                vec[0] = direction.x;
                vec[1] = direction.y;
                vec[2] = direction.z;
            }
        }
    }
    if (max <= 0.0f)
        return 0.0f;
    len = sLenPoint3dR(&push);
    if (0.0f == len)
        return 0.0f;
    if (max > 1.0f)
        max = 1.0f;
    len = max / len;
    vec[0] *= len;
    vec[1] *= len;
    vec[2] *= len;
    for (i = 0; i < 3; i++) {
        d = vec[i];
        plus = d;
        minus = d;
        if (i == 1) {
            if (d < 0.0f)
                plus = 0.0f;
            if (d > 0.0f)
                minus = 0.0f;
        }
        a->position[i] += plus;
        b->position[i] -= minus;
    }
    return max;
}
