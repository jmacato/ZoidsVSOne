#include "zoid.h"

extern void zdGrdCoON(ZoidState *zoid, CoObj *co, s32 flag);

void ZoidGrdON(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        zoid->grounded = 0;
        zoid->max_ground_depth = 0.0f;
        zdGrdCoON(zoid, &zoid->body_coobj, 0);
        zdGrdCoON(zoid, &zoid->head_coobj, 0);
        zdGrdCoON(zoid, &zoid->neck_coobj, 0);
        zdGrdCoON(zoid, &zoid->bust_coobj, 1);
        zdGrdCoON(zoid, &zoid->hip_coobj, 1);
        zdGrdCoON(zoid, &zoid->l_arm1_coobj, 1);
        zdGrdCoON(zoid, &zoid->r_arm1_coobj, 1);
        zdGrdCoON(zoid, &zoid->l_leg1_coobj, 1);
        zdGrdCoON(zoid, &zoid->r_leg1_coobj, 1);
        zdGrdCoON(zoid, &zoid->l_arm2_coobj, 0);
        zdGrdCoON(zoid, &zoid->r_arm2_coobj, 0);
        zdGrdCoON(zoid, &zoid->l_leg2_coobj, 0);
        zdGrdCoON(zoid, &zoid->r_leg2_coobj, 0);
        if (zoid->grounded != 0) {
            zoid->grounded_frames++;
        } else {
            zoid->grounded_frames = 0;
        }
    }
}
