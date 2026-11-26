#include "zoid.h"
#include "game_mode.h"
#include "ground_collision.h"

extern void zdGroundPolyClear(ZoidState *zoid);
extern void angLimit(f32 *angle);
extern void zdCalcRot(ZoidState *zoid);
extern void ZoidMove(ZoidState *zoid);
extern void zdLinier(ZoidState *zoid);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void zdFootBak(ZoidState *zoid);
extern void ZoidDownBody(ZoidState *zoid);
extern void ZoidGround(ZoidState *zoid);
extern void ZoidSpdA(ZoidState *zoid);
extern void ZoidCoBAK(ZoidState *zoid, CoObj *object);
extern void ZoidGrdON(ZoidState *zoid);
extern void zdCalcCoDmg(ZoidState *zoid);
extern void TEA_VoiceOn(u8 character, s32 voice);
extern void PartnerFace(s32 face, s32 frames);
extern s32 sCamNN;
extern s32 gameEndF;

static inline void PAD_STACK(void)
{
    s32 frame_padding[6];
    frame_padding[0] = 0;
}

void ZoidAllMove(void)
{
    ZoidState *zoid;
    ZoidState *partner;
    s32 i;
    s32 pa[2];
    u16 selector;
    f32 before;
    f32 after;

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == 0) {
            continue;
        }
        if (zoid->rumble_timer != 0) {
            zoid->rumble_timer--;
        }
        if (zoid->invulnerable_timer != 0) {
            zoid->invulnerable_timer--;
        }
        if (zoid->health_bar_timer != 0) {
            zoid->health_bar_timer--;
        }
        zdGroundPolyClear(zoid);
        angLimit(&zoid->heading);
        zdCalcRot(zoid);
        angLimit(&zoid->heading);
        ZoidMove(zoid);
        if (zoid->ground_polygon == GROUND_POLYGON_NONE) {
            zoid->position[0] = zoid->previous_position[0];
            zoid->position[1] = zoid->previous_position[1];
            zoid->position[2] = zoid->previous_position[2];
            sColPosY((Vec3 *)zoid->position, &selector);
            if (selector == GROUND_POLYGON_NONE) {
                if (zoid->position[0] < 0.0f) {
                    zoid->position[0] += 1.0f;
                }
                if (zoid->position[2] < 0.0f) {
                    zoid->position[2] += 1.0f;
                }
                if (zoid->position[0] > 0.0f) {
                    zoid->position[0] -= 1.0f;
                }
                if (zoid->position[2] > 0.0f) {
                    zoid->position[2] -= 1.0f;
                }
            }
        }
        zdLinier(zoid);
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
        zdFootBak(zoid);
        if (zoid->death_pending != 0) {
            ZoidDownBody(zoid);
        }
        if (zoid->death_pending == 0) {
            ZoidGround(zoid);
        }
        angLimit(&zoid->heading);
        zoid->previous_animation = zoid->current_animation;
        zoid->field_1A80 = zoid->field_1A74;
        zoid->field_19FC = zoid->position[1] - zoid->previous_position[1];
        zoid->child_matrix[0][0] = zoid->joint->child->matrix[0][0];
        zoid->child_matrix[1][0] = zoid->joint->child->matrix[1][0];
        zoid->child_matrix[2][0] = zoid->joint->child->matrix[2][0];
        zoid->child_matrix[0][1] = zoid->joint->child->matrix[0][1];
        zoid->child_matrix[1][1] = zoid->joint->child->matrix[1][1];
        zoid->child_matrix[2][1] = zoid->joint->child->matrix[2][1];
        zoid->child_matrix[0][2] = zoid->joint->child->matrix[0][2];
        zoid->child_matrix[1][2] = zoid->joint->child->matrix[1][2];
        zoid->child_matrix[2][2] = zoid->joint->child->matrix[2][2];
        zoid->child_matrix[0][3] = zoid->joint->child->matrix[0][3];
        zoid->child_matrix[1][3] = zoid->joint->child->matrix[1][3];
        zoid->child_matrix[2][3] = zoid->joint->child->matrix[2][3];
        zoid->previous_child_translation.x = zoid->joint->child->translation.x;
        zoid->previous_child_translation.y = zoid->joint->child->translation.y;
        zoid->previous_child_translation.z = zoid->joint->child->translation.z;
        zoid->heading_delta = zoid->joint->child->rotation[1];
        ZoidSpdA(zoid);
        ZoidCoBAK(zoid, &zoid->body_coobj);
        ZoidCoBAK(zoid, &zoid->head_coobj);
        ZoidCoBAK(zoid, &zoid->neck_coobj);
        ZoidCoBAK(zoid, &zoid->bust_coobj);
        ZoidCoBAK(zoid, &zoid->hip_coobj);
        ZoidCoBAK(zoid, &zoid->tail_coobjs[0]);
        ZoidCoBAK(zoid, &zoid->l_arm1_coobj);
        ZoidCoBAK(zoid, &zoid->r_arm1_coobj);
        ZoidCoBAK(zoid, &zoid->l_leg1_coobj);
        ZoidCoBAK(zoid, &zoid->r_leg1_coobj);
        ZoidCoBAK(zoid, &zoid->l_arm2_coobj);
        ZoidCoBAK(zoid, &zoid->r_arm2_coobj);
        ZoidCoBAK(zoid, &zoid->l_leg2_coobj);
        ZoidCoBAK(zoid, &zoid->r_leg2_coobj);
        ZoidGrdON(zoid);
        zoid->knockback[0] *= 0.8;
        zoid->knockback[1] *= 0.8;
        zoid->knockback[2] *= 0.8;
        zdCalcCoDmg(zoid);
    }
    zoid = Zoid;
    if (zoid->joint != 0) {
        if (sCamNN == 1 && zoid[2].joint != 0 && zoid->slot == zoid[2].slot && gameEndF == 0 && GameMode.game_type == GAME_TYPE_BATTLE) {
            if ((partner = &zoid[2])->max_health == 0) {
                partner->max_health = 100;
            }
            before = (f32)partner->previous_health / (f32)partner->max_health;
            after = (f32)partner->health / (f32)partner->max_health;
            if (before >= 0.5 && after < 0.5) {
                TEA_VoiceOn(partner->person, 12);
                PartnerFace(4, 60);
            }
            if (partner->previous_health != 0 && partner->health == 0) {
                TEA_VoiceOn(partner->person, 16);
            }
        }
        if (zoid->previous_health != 0 && zoid->health == 0) {
            TEA_VoiceOn(zoid->person, 15);
        }
    }
    if (GameMode.game_type == GAME_TYPE_VS) {
        partner = &Zoid[1];
        if (partner->joint != 0 && partner->previous_health != 0 && partner->health == 0) {
            TEA_VoiceOn(partner->person, 15);
        }
    }
    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != 0) {
            Zoid[i].previous_health = Zoid[i].health;
        }
    }
    PAD_STACK();
}
