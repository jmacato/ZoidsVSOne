#include "zoid.h"

extern s32 ZoidCoObjCoObj(CoObj *a, CoObj *b, s32 flags);

s32 zdCoObj(ZoidState *zoid, CoObj *obj)
{
    s32 hit;
    s32 i;
    s32 frame_padding[2];

    if (zoid == 0)
        return 0;
    if (zoid->joint == 0)
        return 0;
    if (obj == 0)
        return 0;
    if (obj->joint == 0)
        return 0;
    hit = 0;
    ZoidCoObjCoObj(obj, &zoid->head_coobj, 1);
    for (i = 0; i < 8; i++)
        ZoidCoObjCoObj(obj, &zoid->tail_coobjs[i], 1);
    ZoidCoObjCoObj(obj, &zoid->l_arm2_coobj, 1);
    ZoidCoObjCoObj(obj, &zoid->r_arm2_coobj, 1);
    ZoidCoObjCoObj(obj, &zoid->l_leg2_coobj, 1);
    ZoidCoObjCoObj(obj, &zoid->r_leg2_coobj, 1);
    if (ZoidCoObjCoObj(obj, &zoid->neck_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, &zoid->bust_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, &zoid->hip_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, &zoid->l_arm1_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, &zoid->r_arm1_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, &zoid->l_leg1_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, &zoid->r_leg1_coobj, 1) != 0)
        hit = 1;
    return hit;
}
