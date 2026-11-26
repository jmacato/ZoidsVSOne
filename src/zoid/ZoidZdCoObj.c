#include "zoid.h"

extern s32 zdCoObj(ZoidState *zoid, CoObj *co);

s32 ZoidZdCoObj(ZoidState *zoid, ZoidState *other)
{
    s32 hit;
    s32 i;
    s32 frame_padding[2];

    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    if (other == 0) {
        return 0;
    }
    if (other->joint == 0) {
        return 0;
    }
    hit = 0;
    zdCoObj(zoid, &other->head_coobj);
    for (i = 0; i < 8; i++) {
        zdCoObj(zoid, &other->tail_coobjs[i]);
    }
    zdCoObj(zoid, &other->l_arm2_coobj);
    zdCoObj(zoid, &other->r_arm2_coobj);
    zdCoObj(zoid, &other->l_leg2_coobj);
    zdCoObj(zoid, &other->r_leg2_coobj);
    if (zdCoObj(zoid, &other->neck_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, &other->bust_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, &other->hip_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, &other->l_arm1_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, &other->r_arm1_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, &other->l_leg1_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, &other->r_leg1_coobj) != 0) {
        hit = 1;
    }
    return hit;
}
