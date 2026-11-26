#include "zoid.h"
#include "ground_collision.h"
#include "math_support.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern void flyZoid(ZoidState *zoid);
extern void dmgZoid(ZoidState *zoid);
extern f32 sLenPoint3dR(f32 *point);
extern void ZoidToFly(ZoidState *zoid);
extern void ZoidSiseiFace(ZoidState *zoid);
extern f32 zdColPosY(Vec3 *point, u16 *selector);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ZoidWalk(ZoidState *zoid);
extern void ZoidSuberi(ZoidState *zoid);
extern void ZoidJump(ZoidState *zoid);
extern void ZoidTurn(ZoidState *zoid);
extern void ZoidTurnR(ZoidState *zoid, s32 mode);
extern void ZoidTurnL(ZoidState *zoid, s32 mode);
extern void ZoidStop1(ZoidState *zoid);
extern void ZoidDash1(ZoidState *zoid);
extern void ZoidActAtack(ZoidState *zoid);
extern void ZoidActStep(ZoidState *zoid);
extern void ZoidActDmg2(ZoidState *zoid);
extern void ZoidActDmg3(ZoidState *zoid);
extern void ZoidActDeadly(ZoidState *zoid);
extern void ZoidActDead(ZoidState *zoid);
extern void ZoidActDeath(ZoidState *zoid);
extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

static inline void PAD_STACK(void)
{
    s32 frame_padding[5];
    frame_padding[0] = 0;
}

void ZoidMove(ZoidState *zoid)
{
    s32 damage_level;
    ZoidControlData *control;
    s32 state;
    s32 i;
    f32 knockback_length;
    f32 step;
    s32 unused0[1];
    f32 relative;
    s32 unused1[2];
    f32 relative2;
    s32 unused2[1];
    f32 relative3;
    s32 unused3[1];
    f32 magnitude;
    f32 length;
    f32 sum;
    f32 scale;
    Vec3 *normal;
    f32 limit;
    f32 dx;
    f32 dz;

    if (zoid != 0 && zoid->joint != 0) {
        flyZoid(zoid);
        zoid->attack_index = -1;
        control = zoid->control;
        damage_level = 0;
        knockback_length = sLenPoint3dR(zoid->knockback);
        if (knockback_length > 0.5) {
            damage_level = 1;
            if (zoid->jump_phase != 0) {
                damage_level = 2;
            }
        }
        if (knockback_length > 1.5) {
            damage_level = 2;
        }
        ZoidToFly(zoid);
        for (i = 0; i < 3; i++) {
            zoid->previous_position[i] = zoid->position[i];
            if (zoid->sweep_joint != 0) {
                zoid->sweep_origin[i] = zoid->sweep_joint->matrix[i][3];
            }
        }
        if (zoid->health <= 0) {
            zoid->health = 0;
        }
        if (zoid->health == 0) {
            if (zoid->field_1B84 != 0) {
                zoid->field_1B84--;
            }
            if (zoid->field_1B84 == 0) {
                state = zoid->action;
                if (state != ZOID_ACTION_DEAD && state != ZOID_ACTION_DEADLY && state != ZOID_ACTION_DEATH && zoid->death_started == 0) {
                    zoid->action = ZOID_ACTION_DEAD;
                    zoid->requested_action = ZOID_ACTION_DEAD;
                    zoid->action_phase = 0;
                }
            }
        }
        if (control->field_0100 != 0) {
            if (zoid->health == 0) {
                zoid->field_19F0 = 1;
            }
            if (zoid->health > 0 && damage_level == 2) {
                damage_level = 1;
            }
            state = zoid->action;
            if (state == ZOID_ACTION_DEAD || state == ZOID_ACTION_DEADLY || state == ZOID_ACTION_DEATH) {
                damage_level = 0;
                knockback_length = 0.0f;
                if (zoid->requested_action == ZOID_ACTION_DMG2_0) {
                    zoid->requested_action = 0;
                }
                if (zoid->requested_action == ZOID_ACTION_DMG3_0) {
                    zoid->requested_action = 0;
                }
            }
        }
        if (damage_level != 0) {
            zoid->requested_action = ZOID_ACTION_DMG2_0;
            if (damage_level == 2) {
                zoid->requested_action = ZOID_ACTION_DMG3_0;
            }
        }
        if (knockback_length > 0.0f && zoid->health <= 0) {
            zoid->requested_action = ZOID_ACTION_DMG3_0;
            zoid->health = 0;
            if (zoid->action >= ZOID_ACTION_ATTACK_0 && zoid->action <= ZOID_ACTION_ATTACK_9) {
                zoid->action = ZOID_ACTION_WALK;
            }
            if (zoid->action >= ZOID_ACTION_DASH && zoid->action <= ZOID_ACTION_STEP_REQUEST_3) {
                zoid->action = ZOID_ACTION_WALK;
            }
        }
        dmgZoid(zoid);
        if (zoid->field_11E4 != 0) {
            zoid->field_1A34 = 0;
            if (zoid->position[1] > (limit = 1.0f + (2.0f * zoid->displacement[1] + zoid->ground_height))) {
                zoid->position[1] = limit;
            }
            if (zoid->position[1] > zoid->ground_height) {
                zoid->position[1] -= 0.025;
                if (zoid->position[1] < zoid->ground_height) {
                    zoid->position[1] = zoid->ground_height;
                }
            }
            if (zoid->position[1] < zoid->ground_height) {
                zoid->position[1] += 0.025;
                if (zoid->position[1] > zoid->ground_height) {
                    zoid->position[1] = zoid->ground_height;
                }
            }
            if (zoid->face_lock != 0) {
                ZoidSiseiFace(zoid);
            }
            zoid->displacement[0] = 0.0f;
            zoid->velocity[0] = 0.0f;
            zoid->displacement[1] = 0.0f;
            zoid->velocity[1] = 0.0f;
            zoid->displacement[2] = 0.0f;
            zoid->velocity[2] = 0.0f;
            zoid->field_1A74 = 0.0f;
            zoid->forward_speed = 0.0f;
            zoid->ramped_speed = 0.0f;
            zoid->position[1] = zdColPosY((Vec3 *)zoid->position, &zoid->ground_polygon);
            zdSetXYZ(zoid);
            sMakeMatrix(zoid->joint);
            return;
        }
        zoid->death_pending = 0;
        switch (zoid->action) {
        case ZOID_ACTION_WALK:
            zoid->field_1A34 = 0;
            if (zoid->jump_phase != 0) {
                zoid->action = ZOID_ACTION_JUMP_2;
                break;
            }
            ZoidWalk(zoid);
            ZoidSuberi(zoid);
            break;
        case ZOID_ACTION_JUMP_1:
        case ZOID_ACTION_JUMP_2:
            ZoidJump(zoid);
            break;
        case ZOID_ACTION_TURN:
            zoid->field_1A34 = 0;
            ZoidTurn(zoid);
            break;
        case ZOID_ACTION_TURN_R0:
            zoid->field_1A34 = 0;
            ZoidTurnR(zoid, 0);
            break;
        case ZOID_ACTION_TURN_R1:
            zoid->field_1A34 = 0;
            ZoidTurnR(zoid, 1);
            break;
        case ZOID_ACTION_TURN_R2:
            zoid->field_1A34 = 0;
            ZoidTurnR(zoid, 2);
            break;
        case ZOID_ACTION_TURN_L0:
            zoid->field_1A34 = 0;
            ZoidTurnL(zoid, 0);
            break;
        case ZOID_ACTION_TURN_L1:
            zoid->field_1A34 = 0;
            ZoidTurnL(zoid, 1);
            break;
        case ZOID_ACTION_TURN_L2:
            zoid->field_1A34 = 0;
            ZoidTurnL(zoid, 2);
            break;
        case ZOID_ACTION_STOP:
            zoid->field_1A34 = 0;
            ZoidStop1(zoid);
            break;
        case ZOID_ACTION_DASH:
            zoid->field_1A34 = 0;
            ZoidDash1(zoid);
            break;
        case ZOID_ACTION_ATTACK_0:
        case ZOID_ACTION_ATTACK_1:
        case ZOID_ACTION_ATTACK_2:
        case ZOID_ACTION_ATTACK_3:
        case ZOID_ACTION_ATTACK_4:
        case ZOID_ACTION_ATTACK_5:
        case ZOID_ACTION_ATTACK_6:
        case ZOID_ACTION_ATTACK_7:
        case ZOID_ACTION_ATTACK_8:
        case ZOID_ACTION_ATTACK_9:
            zoid->attack_index = zoid->action - ZOID_ACTION_ATTACK_0;
            zoid->field_1A34 = 1;
            ZoidActAtack(zoid);
            break;
        case ZOID_ACTION_STEP_0:
        case ZOID_ACTION_STEP_1:
        case ZOID_ACTION_STEP_2:
        case ZOID_ACTION_STEP_3:
            zoid->field_1A34 = 1;
            ZoidActStep(zoid);
            break;
        case ZOID_ACTION_DMG2_0:
        case ZOID_ACTION_DMG2_1:
        case ZOID_ACTION_DMG2_2:
        case ZOID_ACTION_DMG2_3:
        case ZOID_ACTION_DMG2_4:
        case ZOID_ACTION_DMG2_5:
        case ZOID_ACTION_DMG2_6:
            zoid->field_1A34 = 0;
            ZoidActDmg2(zoid);
            break;
        case ZOID_ACTION_DMG3_0:
        case ZOID_ACTION_DMG3_1:
        case ZOID_ACTION_DMG3_2:
        case ZOID_ACTION_DMG3_3:
        case ZOID_ACTION_DMG3_4:
        case ZOID_ACTION_DMG3_5:
        case ZOID_ACTION_DMG3_6:
            zoid->field_1A34 = 1;
            ZoidActDmg3(zoid);
            break;
        case ZOID_ACTION_DEADLY:
            zoid->field_1A34 = 0;
            ZoidActDeadly(zoid);
            if (zoid->health == 0) {
                return;
            }
            break;
        case ZOID_ACTION_DEAD:
            zoid->field_1A34 = 1;
            ZoidActDead(zoid);
            if (zoid->health == 0) {
                return;
            }
            break;
        case ZOID_ACTION_DEATH:
            zoid->field_1A34 = 1;
            ZoidActDeath(zoid);
            if (zoid->health == 0) {
                return;
            }
            break;
        default:
            zoid->field_1A34 = 0;
            break;
        }
        if (zoid->action != ZOID_ACTION_WALK) {
            return;
        }
        switch (zoid->requested_action) {
        case ZOID_ACTION_JUMP_1:
        case ZOID_ACTION_JUMP_2:
            zoid->action_phase = 0;
            zoid->jump_phase = zoid->requested_action;
            zoid->action = zoid->requested_action;
            zoid->requested_action = 0;
            break;
        case ZOID_ACTION_TURN:
        case ZOID_ACTION_TURN_R0:
        case ZOID_ACTION_TURN_L0:
        case ZOID_ACTION_TURN_R1:
        case ZOID_ACTION_TURN_L1:
        case ZOID_ACTION_TURN_R2:
        case ZOID_ACTION_TURN_L2:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case ZOID_ACTION_STOP:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case ZOID_ACTION_ATTACK_0:
        case ZOID_ACTION_ATTACK_1:
        case ZOID_ACTION_ATTACK_2:
        case ZOID_ACTION_ATTACK_3:
        case ZOID_ACTION_ATTACK_4:
        case ZOID_ACTION_ATTACK_5:
        case ZOID_ACTION_ATTACK_6:
        case ZOID_ACTION_ATTACK_7:
        case ZOID_ACTION_ATTACK_8:
        case ZOID_ACTION_ATTACK_9:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case ZOID_ACTION_STEP_0:
        case ZOID_ACTION_STEP_1:
        case ZOID_ACTION_STEP_2:
        case ZOID_ACTION_STEP_3:
            step = zoid->step_heading;
            relative = step - zoid->heading;
            angLimit(&relative);
            magnitude = absf(relative);
            if (magnitude < DEG(45)) {
                zoid->action = ZOID_ACTION_STEP_0;
            } else if (magnitude > DEG(135)) {
                zoid->action = ZOID_ACTION_STEP_1;
            } else if (relative > 0.0f) {
                zoid->action = ZOID_ACTION_STEP_3;
            } else {
                zoid->action = ZOID_ACTION_STEP_2;
            }
            zoid->launch_velocity.x = zoid->displacement[0] + sinf(step);
            zoid->launch_velocity.z = zoid->displacement[2] + cosf(step);
        case ZOID_ACTION_STEP_REQUEST_0:
        case ZOID_ACTION_STEP_REQUEST_1:
        case ZOID_ACTION_STEP_REQUEST_2:
        case ZOID_ACTION_STEP_REQUEST_3:
            if (zoid->requested_action == ZOID_ACTION_STEP_REQUEST_0) {
                zoid->action = ZOID_ACTION_STEP_0;
            }
            if (zoid->requested_action == ZOID_ACTION_STEP_REQUEST_1) {
                zoid->action = ZOID_ACTION_STEP_1;
            }
            if (zoid->requested_action == ZOID_ACTION_STEP_REQUEST_2) {
                zoid->action = ZOID_ACTION_STEP_2;
            }
            if (zoid->requested_action == ZOID_ACTION_STEP_REQUEST_3) {
                zoid->action = ZOID_ACTION_STEP_3;
            }
            zoid->launch_velocity.y = 0.01 * (f32)control->step_launch_y + zoid->displacement[1];
            if (zoid->launch_velocity.y > 1.0f) {
                zoid->launch_velocity.y = 1.0f;
            }
            if (zoid->ground_polygon != GROUND_POLYGON_NONE) {
                normal = &grdcNormal[grdcPolygon[zoid->ground_polygon].normal_index];
                zoid->launch_velocity.x += normal->x;
                zoid->launch_velocity.z += normal->z;
                zoid->launch_velocity.y *= normal->y;
            }
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case ZOID_ACTION_DMG2_0:
            if (absf(zoid->knockback[1]) >= absf(zoid->knockback[0]) && absf(zoid->knockback[1]) >= absf(zoid->knockback[2])) {
                if (zoid->knockback[1] > 0.0f) {
                    zoid->action = ZOID_ACTION_DMG2_6;
                } else {
                    zoid->action = ZOID_ACTION_DMG2_5;
                }
            } else {
                dz = zoid->knockback[2];
                dx = zoid->knockback[0];
                relative2 = atan2f(dx, dz) - zoid->heading;
                angLimit(&relative2);
                magnitude = absf(relative2);
                if (relative2 > 0.0f) {
                    zoid->action = ZOID_ACTION_DMG2_3;
                } else {
                    zoid->action = ZOID_ACTION_DMG2_2;
                }
                if (magnitude < DEG(45)) {
                    zoid->action = ZOID_ACTION_DMG2_4;
                }
                if (magnitude > DEG(135)) {
                    zoid->action = ZOID_ACTION_DMG2_1;
                }
            }
            zoid->knockback[0] += zoid->displacement[0];
            zoid->knockback[2] += zoid->displacement[2];
        case ZOID_ACTION_DMG2_1:
        case ZOID_ACTION_DMG2_2:
        case ZOID_ACTION_DMG2_3:
        case ZOID_ACTION_DMG2_4:
        case ZOID_ACTION_DMG2_5:
        case ZOID_ACTION_DMG2_6:
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        case ZOID_ACTION_DMG3_0:
            length = sLenPoint3dR(zoid->knockback);
            if (length > 2.0f) {
                zoid->knockback[0] = 2.0f * (zoid->knockback[0] / length);
                zoid->knockback[1] = 2.0f * (zoid->knockback[1] / length);
                zoid->knockback[2] = 2.0f * (zoid->knockback[2] / length);
            }
            if (absf(zoid->knockback[1]) >= absf(zoid->knockback[0]) && absf(zoid->knockback[1]) >= absf(zoid->knockback[2])) {
                zoid->knockback[1] = 0.4 * ((f32)control->dmg3_launch_scale / 100.0);
                if (zoid->knockback[1] > 0.0f) {
                    zoid->action = ZOID_ACTION_DMG3_6;
                } else {
                    zoid->action = ZOID_ACTION_DMG3_5;
                }
            } else {
                dz = zoid->knockback[2];
                dx = zoid->knockback[0];
                relative3 = atan2f(dx, dz) - zoid->heading;
                angLimit(&relative3);
                magnitude = absf(relative3);
                if (relative3 > 0.0f) {
                    zoid->action = ZOID_ACTION_DMG3_3;
                } else {
                    zoid->action = ZOID_ACTION_DMG3_2;
                }
                if (magnitude < DEG(45)) {
                    zoid->action = ZOID_ACTION_DMG3_4;
                }
                if (magnitude > DEG(135)) {
                    zoid->action = ZOID_ACTION_DMG3_1;
                }
                zoid->knockback[1] = 0.4 * ((f32)control->dmg3_launch_scale / 100.0);
            }
        case ZOID_ACTION_DMG3_1:
        case ZOID_ACTION_DMG3_2:
        case ZOID_ACTION_DMG3_3:
        case ZOID_ACTION_DMG3_4:
        case ZOID_ACTION_DMG3_5:
        case ZOID_ACTION_DMG3_6:
            sum = 0.0f;
            for (i = 0; i < 3; i++) {
                f32 v = zoid->knockback[i];
                (&zoid->launch_velocity.x)[i] = v;
                sum += v * v;
            }
            length = square_root(sum);
            if (length > 2.0f) {
                zoid->launch_velocity.x = 2.0f * zoid->knockback[0] / length;
                zoid->launch_velocity.y = 2.0f * zoid->knockback[1] / length;
                zoid->launch_velocity.z = 2.0f * zoid->knockback[2] / length;
            }
            scale = (f32)control->dmg3_launch_scale * (f32)control->dmg3_launch_scale / 100.0 / 100.0;
            zoid->launch_velocity.x *= scale;
            zoid->launch_velocity.z *= scale;
            zoid->launch_velocity.y = (f32)control->dmg3_launch_scale / 100.0;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            zoid->knockback[0] += zoid->displacement[0];
            zoid->knockback[2] += zoid->displacement[2];
            break;
        case ZOID_ACTION_DEADLY:
        case ZOID_ACTION_DEAD:
        case ZOID_ACTION_DEATH:
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        }
        PAD_STACK();
    }
}
