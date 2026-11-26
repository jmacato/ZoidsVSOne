#include "zoid.h"

extern s32 zdShadowLo(void *shadow, CoObj *co);

void ZoidShadowLo(void *shadow, ZoidState *zoid)
{
    s32 i;

    if (zoid->joint == 0) {
        return;
    }
    if (zdShadowLo(shadow, &zoid->bust_coobj) != 0) {
        if (zdShadowLo(shadow, &zoid->neck_coobj) != 0) {
            zdShadowLo(shadow, &zoid->head_coobj);
        }
    }
    zdShadowLo(shadow, &zoid->hip_coobj);
    for (i = 0; i < 8; i++) {
        zdShadowLo(shadow, &zoid->tail_coobjs[i]);
    }
    zdShadowLo(shadow, &zoid->l_arm1_coobj);
    zdShadowLo(shadow, &zoid->l_arm2_coobj);
    zdShadowLo(shadow, &zoid->r_arm1_coobj);
    zdShadowLo(shadow, &zoid->r_arm2_coobj);
    zdShadowLo(shadow, &zoid->l_leg1_coobj);
    zdShadowLo(shadow, &zoid->l_leg2_coobj);
    zdShadowLo(shadow, &zoid->r_leg1_coobj);
    zdShadowLo(shadow, &zoid->r_leg2_coobj);
    zdShadowLo(shadow, &zoid->l_foot_coobj);
    zdShadowLo(shadow, &zoid->r_foot_coobj);
}
