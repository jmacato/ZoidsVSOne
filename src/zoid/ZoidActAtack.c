#include "zoid.h"
#include "angle.h"
#include "game_mode.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern f32 beSide(f32 current, f32 target, f32 step);
extern void ZoidSisei(ZoidState *zoid);
extern void zdAtkSub(ZoidState *zoid);
extern void zdAtkSubFor(ZoidState *zoid, s32 attack);
extern void zdAtkSubForPullLen(ZoidState *zoid, s32 attack);
extern void zdAtkSubForPull2(ZoidState *zoid);
extern s32 zdFaceAtk(ZoidState *zoid, f32 distance);
extern f32 zdGoYA(ZoidState *zoid, f32 a, f32 b);
extern void coBakAtk(ZoidState *zoid);
extern void zdAtackSetEffect(ZoidState *zoid, s32 effect);
extern s32 HSD_Randi(s32 maximum);
extern void TEA_VoiceOn(u8 character, s32 voice);
extern void ZoidInertia(ZoidState *zoid);
extern void ZoidInertiaAtk(ZoidState *zoid);
extern void setAnimRateXor(HSD_JObj *joint, f32 rate, HSD_JObj *excluded);
extern s32 zdAtkSubLakka(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void zdChgNormal(ZoidState *zoid);

void ZoidActAtack(ZoidState *zoid)
{
    s32 start[5] = {88, 90, 92, 94, 96};
    s32 loop[5] = {89, 91, 93, 95, 97};
    ZoidControlData *control;
    s32 attack;
    s32 ok;
    s32 busy;
    s32 hit;
    s32 voice;
    s32 request;
    s32 flags;
    s32 wait;

    if (zoid == 0) {
        return;
    }
    control = zoid->control;
    if (control == 0) {
        return;
    }
    busy = 0;
    request = zoid->requested_action;
    if (request == ZOID_ACTION_DMG2_0) busy = 1;
    if (request == ZOID_ACTION_DMG3_0) busy = 1;
    if (busy != 0) {
        zoid->action_phase = 153;
    }
    attack = zoid->action - ZOID_ACTION_ATTACK_0;
    zoid->face_yaw = beSide(zoid->face_yaw, 0.0f, DEG2RAD_F(5.0f));
    zoid->face_pitch = beSide(zoid->face_pitch, 0.0f, DEG2RAD_F(5.0f));
    zoid->senter_roll = beSide(zoid->senter_roll, 0.0f, DEG2RAD_F(5.0f));
    zoid->f_base_ry = beSide(zoid->f_base_ry, 0.0f, DEG2RAD_F(5.0f));
    ZoidSisei(zoid);
    zdAtkSub(zoid);
    zdAtkSubFor(zoid, attack);
    zdAtkSubForPullLen(zoid, attack);
    zdAtkSubForPull2(zoid);
    switch (zoid->action_phase) {
    case 0:
        ok = 1;
        if (zdFaceAtk(zoid, 5.0f) != 0) ok = 0;
        if (zdGoYA(zoid, 0.0f, 0.5f) > 1.0f) ok = 0;
        if (zdGoYA(zoid, 0.0f, 1.0f) > 1.0f) ok = 0;
        if (zdGoYA(zoid, 0.0f, 2.0f) > 1.0f) ok = 0;
        if (zdGoYA(zoid, 0.0f, 5.0f) > 1.0f) ok = 0;
        if (ok == 0) {
            zoid->action_phase = 153;
        }
        if (zoid->type == 0 && zoid->sweep_hit != 0) {
            ok = 0;
        }
        flags = control->field_00F4;
        if (flags == 4 && control->field_00F8 == 0 && zoid->grounded == 0) {
            ok = 0;
        }
        if (flags == 0 && zoid->grounded == 0) {
            if (zoid->feet[0].joint != 0 && zoid->feet[1].joint != 0) {
                if (!(zoid->feet[0].flags & FOOT_FLAG_CONTACT) && !(zoid->feet[1].flags & FOOT_FLAG_CONTACT)) {
                    ok = 0;
                }
            } else {
                ok = 0;
            }
        }
        if (control->field_00F8 == 1) {
            ok = 1;
        }
        if (ok == 0) {
            if ((u32)zoid->bust_coobj.object_contact != 0) {
                zoid->action_phase = 153;
            }
            if ((u32)zoid->hip_coobj.object_contact != 0) {
                zoid->action_phase = 153;
            }
            coBakAtk(zoid);
            break;
        }
        ZoidSetAnim(zoid, start[zoid->action - ZOID_ACTION_ATTACK_0]);
        zdAtackSetEffect(zoid, attack);
        zoid->action_phase = 1;
        zdAtkSub(zoid);
        if (zoid->action == ZOID_ACTION_ATTACK_0) {
            voice = 1;
            if (GameMode.game_type == GAME_TYPE_VS) {
                voice = 0;
            }
            if (GameMode.game_type != GAME_TYPE_VS && zoid->slot != Zoid[0].slot) {
                voice = 0;
            }
            if (voice != 0) {
                TEA_VoiceOn(zoid->person, HSD_Randi(3) + 3);
            }
        }
        break;
    case 17:
        if (zoid->grounded != 0) {
            zoid->action_phase = 18;
            zoid->grounded_frames = 0;
        }
        ZoidInertia(zoid);
        zoid->unsupported_frames = 0;
        break;
    case 18:
        hit = 0;
        zoid->grounded_frames++;
        if (control->field_00F4 != 0) {
            if (zoid->r_leg2_coobj.joint != 0 && ((u32)zoid->r_leg2_coobj.object_contact != 0 || (u32)zoid->r_leg2_coobj.ground_contact != 0)) {
                hit = 1;
            }
            if (zoid->l_leg2_coobj.joint != 0 && ((u32)zoid->l_leg2_coobj.object_contact != 0 || (u32)zoid->l_leg2_coobj.ground_contact != 0)) {
                hit = 1;
            }
            if (zoid->head_coobj.joint != 0 && ((u32)zoid->head_coobj.object_contact != 0 || (u32)zoid->head_coobj.ground_contact != 0)) {
                hit = 1;
            }
            if ((zoid->feet[2].flags & FOOT_FLAG_CONTACT) || (zoid->feet[3].flags & FOOT_FLAG_CONTACT)) {
                hit = 1;
            }
        }
        if (zoid->grounded_frames > 6) {
            hit = 1;
        }
        if (zoid->grounded != 0) {
            hit = 1;
        }
        if (hit != 0) {
            zoid->displacement[0] = 0.0f;
            zoid->displacement[2] = 0.0f;
            if (zoid->displacement[1] > 0.0f) {
                zoid->displacement[1] = 0.9f;
            }
            zoid->displacement[1] = 0.9f;
            zoid->action_phase = 19;
            setAnimRateXor(zoid->joint, 1.0f, zoid->animation_exclusion);
        } else {
            ZoidInertiaAtk(zoid);
            zoid->unsupported_frames = 0;
        }
        break;
    case 1:
        if (zdAtkSubLakka(zoid) != 0) {
            zoid->action_phase = 17;
            break;
        }
        if (zoid->type == 0 && zoid->sweep_hit != 0) {
            zoid->action_phase = 153;
        }
        if ((u32)zoid->head_coobj.ground_contact != 0 || (u32)zoid->neck_coobj.ground_contact != 0 || zdFaceAtk(zoid, attack) != 0) {
            zoid->joint->child->translation.x = zoid->previous_child_translation.x;
            zoid->joint->child->translation.y = zoid->previous_child_translation.y;
            zoid->joint->child->translation.z = zoid->previous_child_translation.z;
            sMakeMatrix(zoid->joint->child);
        }
        wait = 0;
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            wait = 1;
        }
        if (wait != 0) {
            break;
        }
    case 19:
        if (zoid->requested_action == ZOID_ACTION_ATTACK_0 && attack + 1 < control->attack_chain_length) {
            zoid->action++;
            zoid->action_phase = 0;
            zoid->requested_action = 0;
            break;
        }
        zoid->action_phase = 2;
    case 2:
        ZoidSetAnim(zoid, loop[zoid->action - ZOID_ACTION_ATTACK_0]);
        zoid->displacement[0] = 0.0f;
        zoid->displacement[1] = 0.0f;
        zoid->displacement[2] = 0.0f;
        zoid->action_phase = 3;
    case 3:
        if (zdAtkSubLakka(zoid) != 0) {
            zoid->action_phase = 49;
            break;
        }
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
    default:
        zoid->action = ZOID_ACTION_WALK;
        if (zoid->requested_action == ZOID_ACTION_DMG2_0) {
            zdChgNormal(zoid);
            zoid->requested_action = ZOID_ACTION_DMG2_0;
        } else if (zoid->requested_action == ZOID_ACTION_DMG3_0) {
            zdChgNormal(zoid);
            zoid->requested_action = ZOID_ACTION_DMG3_0;
        } else {
            zoid->requested_action = 0;
            zdChgNormal(zoid);
        }
        break;
    case 49:
        if (zoid->displacement[1] > 0.0f) {
            zoid->displacement[1] = 0.0f;
        }
        if (zoid->launch_velocity.y > 0.0f) {
            zoid->launch_velocity.y = 0.0f;
        }
        if (zoid->grounded != 0) {
            zoid->action_phase = 3;
            zoid->grounded_frames = 0;
        }
        ZoidInertia(zoid);
        zoid->unsupported_frames = 0;
        break;
    }
}
