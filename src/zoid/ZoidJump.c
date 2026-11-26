#include "zoid.h"
#include "ground_collision.h"
#include "missile.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void zdAtackSetEffect(ZoidState *zoid, s32 effect);
extern void zdLinierTm(ZoidState *zoid, s32 frames);
extern void zdVaSet(ZoidState *zoid);
extern void zdJumpMove(ZoidState *zoid);
extern void ZoidWalkJ(ZoidState *zoid);
extern void ZoidWalk(ZoidState *zoid);
extern double sin(double x);
extern double cos(double x);

void ZoidJump(ZoidState *zoid)
{
    s32 frame_padding[2];
    f32 power[41] = {
        0.0f, 0.3f, 0.34f, 0.4f, 0.47f, 0.5f, 0.57f, 0.6f, 0.66f, 0.69f, 0.7f, 0.76f, 0.79f, 0.8f,
        0.831f, 0.865f, 0.9f, 0.93f, 0.96f, 0.985f, 1.0f, 1.03f, 1.06f, 1.08f, 1.1f, 1.12f, 1.14f,
        1.16f, 1.18f, 1.2f, 1.22f, 1.24f, 1.26f, 1.28f, 1.3f, 1.32f, 1.34f, 1.36f, 1.38f, 1.4f, 0.0f,
    };
    ZoidControlData *control;
    s32 state;
    s32 anim;
    s32 landed;
    s32 mode;
    f32 turn;
    f32 dx;
    f32 push;
    f32 dz;
    Vec3 *normal;

    if (zoid->requested_action == ZOID_ACTION_JUMP_1 || zoid->requested_action == ZOID_ACTION_JUMP_2) {
        zoid->requested_action = 0;
    }
    state = zoid->jump_phase;
    control = zoid->control;
    turn = zoid->field_1A74;
    if ((state == 17 || state == 33) && zoid->jump_attack_phase == 0 && zoid->requested_action == ZOID_ACTION_ATTACK_0) {
        ZoidSetAnim(zoid, 86);
        zdAtackSetEffect(zoid, 5);
        zoid->requested_action = 0;
        zoid->jump_attack_phase = 1;
    }
    if (zoid->jump_attack_phase == 1 && zoid->animation_stopped != 0) {
        ZoidSetAnim(zoid, 87);
        zoid->requested_action = 0;
        zoid->jump_attack_phase = 2;
    }
    if (zoid->jump_attack_phase != 0) {
        zoid->attack_index = 5;
    }
    switch (state) {
    case 1:
    case 2:
        sEffectSet(60, 1, 0, zoid->f_base_joint, 0);
        zoid->jump_attack_phase = 0;
        zoid->velocity[0] = 0.0f;
        zoid->velocity[2] = 0.0f;
        zoid->velocity[1] = power[((s32 *)&control->field_009C)[state]];
        if (zoid->ground_polygon != GROUND_POLYGON_NONE) {
            normal = &grdcNormal[grdcPolygon[zoid->ground_polygon].normal_index];
            zoid->velocity[0] = 0.01 * normal->x;
            zoid->velocity[2] = 0.01 * normal->z;
            zoid->velocity[1] *= normal->y;
        }
        if (zoid->senter_joint != 0) {
            push = 0.02 * zoid->senter_roll;
            dx = push * sin(DEG(90) + zoid->heading);
            dz = push * cos(DEG(90) + zoid->heading);
            zoid->velocity[0] += dx;
            zoid->velocity[2] += dz;
        }
        anim = 12;
        if (turn > 0.0f) {
            anim = 16;
        } else if (turn < 0.0f) {
            anim = 20;
        }
        ZoidSetAnim(zoid, anim);
        zoid->jump_phase = 3;
        break;
    case 3:
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            anim = 13;
            if (turn > 0.0f) {
                anim = 17;
            } else if (turn < 0.0f) {
                anim = 21;
            }
            zoid->jump_phase = 16;
            ZoidSetAnim(zoid, anim);
            zoid->jump_attack_phase = 0;
        }
        break;
    case 16:
        anim = 13;
        if (turn > 0.0f) {
            anim = 17;
        } else if (turn < 0.0f) {
            anim = 21;
        }
        if (zoid->current_animation != anim) {
            ZoidSetAnim(zoid, anim);
            zdLinierTm(zoid, 30);
        }
        zoid->jump_phase = 17;
        break;
    case 17:
        zdJumpMove(zoid);
        if (zoid->velocity[1] < 0.0f) {
            zoid->jump_phase = 32;
        }
        if (zoid->velocity[1] < 0.5) {
            zoid->jump_phase = 18;
        }
        break;
    case 18:
        zdJumpMove(zoid);
        if (zoid->velocity[1] < 0.0f) {
            zoid->jump_phase = 32;
        }
        if (zoid->jump_attack_phase == 0) {
            anim = 14;
            if (turn > 0.0f) {
                anim = 18;
            } else if (turn < 0.0f) {
                anim = 22;
            }
            if (zoid->current_animation != anim) {
                ZoidSetAnim(zoid, anim);
                zdLinierTm(zoid, 240);
            }
        }
        break;
    case 32:
        if (zoid->jump_attack_phase == 0) {
            anim = 14;
            if (turn > 0.0f) {
                anim = 18;
            } else if (turn < 0.0f) {
                anim = 22;
            }
            if (zoid->current_animation != anim) {
                ZoidSetAnim(zoid, anim);
                zdLinierTm(zoid, 240);
            }
        }
        zoid->jump_phase = 33;
    case 33:
        zdVaSet(zoid);
        zdJumpMove(zoid);
        landed = 0;
        if (control->field_00F4 != 0) {
            if (zoid->feet[2].joint != 0 && (zoid->feet[2].flags & FOOT_FLAG_CONTACT)) {
                landed = 1;
            }
            if (zoid->feet[3].joint != 0 && (zoid->feet[3].flags & FOOT_FLAG_CONTACT)) {
                landed = 1;
            }
            if (zoid->r_leg2_coobj.joint != 0 && ((u32)zoid->r_leg2_coobj.object_contact != 0 || (u32)zoid->r_leg2_coobj.ground_contact != 0)) {
                landed = 1;
            }
            if (zoid->r_leg1_coobj.joint != 0 && ((u32)zoid->r_leg1_coobj.object_contact != 0 || (u32)zoid->r_leg1_coobj.ground_contact != 0)) {
                landed = 1;
            }
            if (zoid->l_leg2_coobj.joint != 0 && ((u32)zoid->l_leg2_coobj.object_contact != 0 || (u32)zoid->l_leg2_coobj.ground_contact != 0)) {
                landed = 1;
            }
            if (zoid->l_leg1_coobj.joint != 0 && ((u32)zoid->l_leg1_coobj.object_contact != 0 || (u32)zoid->l_leg1_coobj.ground_contact != 0)) {
                landed = 1;
            }
        } else if (zoid->foot_contacts != 0 || zoid->grounded != 0) {
            landed = 1;
        }
        if (zoid->displacement[1] > 0.0f) {
            landed = 1;
        }
        if ((u32)zoid->bust_coobj.ground_contact != 0) {
            landed = 1;
        }
        if (landed != 0) {
            zoid->jump_phase = 48;
            zoid->field_1B24 = 60;
        }
        break;
    case 48:
        zoid->jump_attack_phase = 0;
        if (zoid->velocity[1] > -1.2) {
            zoid->action = ZOID_ACTION_WALK;
            zoid->jump_phase = 0;
            if (zoid->velocity[1] < -0.8) {
                sEffectSet(60, 1, 0, zoid->f_base_joint, 0);
            }
            ZoidSetAnim(zoid, 1);
        } else {
            anim = 15;
            if (turn > 0.0f) {
                anim = 19;
            } else if (turn < 0.0f) {
                anim = 23;
            }
            sEffectSet(60, 1, 0, zoid->f_base_joint, 0);
            ZoidSetAnim(zoid, anim);
            zoid->jump_phase = 49;
        }
        break;
    case 49:
        zoid->jump_attack_phase = 0;
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->jump_phase = 0;
            zoid->action = ZOID_ACTION_WALK;
            ZoidSetAnim(zoid, 1);
        }
        break;
    }
    mode = 2;
    if (zoid->jump_phase == 1) {
        mode = 1;
    }
    if (zoid->jump_phase == 48) {
        mode = 0;
    }
    if (zoid->jump_phase == 49) {
        mode = 0;
    }
    if (mode == 2) {
        ZoidWalkJ(zoid);
    }
    if (mode == 1) {
        ZoidWalk(zoid);
    }
}
