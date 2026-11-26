#include "zoid.h"

#define NULL 0

u32 zdsMotTBL[1359] = {
    0, 0, 2, 0, 0, 0, 0, 2, 2, 150, 150, 150, 150, 148, 148, 3,
    150, 148, 148, 3, 150, 148, 148, 3, 242, 240, 240, 243, 242, 240, 240, 243,
    242, 240, 240, 243, 242, 240, 240, 243, 243, 243, 243, 11, 11, 11, 11, 11,
    11, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243,
    243, 243, 243, 243, 243, 243, 241, 243, 243, 243, 243, 243, 243, 243, 243, 242,
    240, 240, 242, 242, 10, 10, 250, 250, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 8, 10, 250, 240, 10, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0,
};

s32 wpTbl[6][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2},
    {2, 2, 1, 2, 2, 0, 0},
    {1, 1, 1, 2, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0},
};

extern s32 getEndFA(HSD_JObj *joint);
extern s32 zdGetAnimNum(ZoidState *zoid, HSD_JObj *joint);
extern void ZoidSetAnimAllPoint(ZoidState *zoid, HSD_JObj *joint, s32 animation);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void zdSearchSight(ZoidState *zoid, s32 index);
extern s32 zdWeaponWpOFF(ZoidState *zoid, WeaponMount *mount);
extern s32 zdWeaponWpON(ZoidState *zoid, WeaponMount *mount);
extern void zdWeaponFire1(ZoidState *zoid);
extern void zdWeaponFireOFF(ZoidState *zoid);
extern void TEA_VoiceOn(u8 person, s32 voice);

void zdWeaponActLoop(ZoidState *zoid)
{
    WeaponMount *mount;
    s32 state;
    HSD_JObj *target;
    s32 anim;
    s32 i;
    s32 end;
    s32 kind;
    s32 type;
    s32 cur;
    s32 want;
    s32 off;
    s32 next;
    s32 mode;
    s32 action;
    ZoidControlData *ctl;

    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    ctl = zoid->control;
    if (ctl->field_0140[zoid->selected_weapon_mount] == 2 && zoid->action != ZOID_ACTION_WALK)
        return;
    if (zoid->requested_action == ZOID_ACTION_DMG2_0 || zoid->requested_action == ZOID_ACTION_DMG3_0 ||
        (zoid->action >= ZOID_ACTION_DMG2_0 && zoid->action <= ZOID_ACTION_DMG2_6) ||
        (zoid->action >= ZOID_ACTION_DMG3_0 && zoid->action <= ZOID_ACTION_DMG3_6))
    {
        zoid->super_attack_input = 0;
        if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK)
            zoid->selected_weapon_mount = -1;
        type = ctl->field_0140[zoid->selected_weapon_mount];
        kind = wpTbl[type][zoid->weapon_mounts[zoid->selected_weapon_mount].state];
        if (type == 2 || kind == 2) {
            zoid->selected_weapon_mount = -1;
            return;
        }
    }
    if (zoid->health == 0)
        zoid->selected_weapon_mount = -1;
    if ((zoid->requested_action >= ZOID_ACTION_DMG2_0 && zoid->requested_action == ZOID_ACTION_DMG3_6) ||
        (zoid->action >= ZOID_ACTION_DMG2_0 && zoid->action == ZOID_ACTION_DMG3_6))
    {
        kind = zoid->weapon_slots[zoid->weapon_mount].field_04;
        zoid->selected_weapon_mount = -1;
        if (kind == 6) {
            zoid->weapon_mount = -1;
            return;
        }
    }
    if (zoid->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK && zoid->selected_weapon_mount == -1)
        zoid->super_attack_input = 0;
    if (zoid->super_attack_cooldown != 0)
        zoid->super_attack_cooldown--;
    if (zoid->super_attack_input != 0 && zoid->super_attack_enabled != 0 && zoid->super_attack_cooldown == 0) {
        zoid->selected_weapon_mount = WEAPON_MOUNT_SUPER_ATTACK;
        zoid->face_lock = 1;
    }
    zoid->field_11E4 = 0;
    target = NULL;
    cur = zoid->weapon_mount;
    want = zoid->selected_weapon_mount;
    if (zoid->attack_index != -1)
        want = -1;
    if (cur == -1) {
        zoid->weapon_mount = want;
        /* the cast is needed: a plain member store changes the code */
        *(s32 *)&zoid->weapon_mounts[want].state = 0;
        cur = want;
    }
    if (cur == -1)
        return;
    mount = &zoid->weapon_mounts[cur];
    if (cur >= 10)
        mount->active = 1;
    state = mount->state;
    anim = cur * 5 + 104;
    if (cur == WEAPON_MOUNT_SUPER_ATTACK)
        anim = 98;
    type = ctl->field_0140[cur];
    if (type == 2 || (u32)(type - 3) <= 1) {
        if (zoid->jump_phase != 0)
            return;
        if (zoid->action == ZOID_ACTION_STEP_3)
            return;
        if (zoid->action == ZOID_ACTION_STEP_2)
            return;
        if (zoid->action == ZOID_ACTION_STEP_0)
            return;
        if (zoid->action == ZOID_ACTION_STEP_1)
            return;
    }
    kind = wpTbl[type][state];
    if (kind == 1)
        target = zoid->animation_exclusion;
    if (kind == 2)
        target = zoid->joint->child;
    if (cur != want) {
        if (cur < 10 && mount->active == 0) {
            mount->state = 0;
            zoid->weapon_mount = want;
            return;
        }
        if (target == NULL) {
            mount->state = 0;
        } else {
            end = 0;
            if (kind == 1)
                end = getEndFA(target);
            if (kind == 2)
                end = zoid->animation_looped | zoid->animation_stopped;
            if (kind == 2)
                zoid->field_11E4 = 1;
            if (state != 0) {
                if (state == 3 && end == 0) {
                    if (kind == 2 && ((u32)zoid->head_coobj.ground_contact != 0 || (u32)zoid->neck_coobj.ground_contact != 0)) {
                        zoid->joint->child->translation.x = zoid->previous_child_translation.x;
                        zoid->joint->child->translation.y = zoid->previous_child_translation.y;
                        zoid->joint->child->translation.z = zoid->previous_child_translation.z;
                    }
                    return;
                }
                if (state == 2 || state == 3 || end != 0) {
                    next = 3;
                    if (state == 4)
                        next = 4;
                    if (kind == 1)
                        ZoidSetAnimAllPoint(zoid, target, anim + next);
                    if (kind == 2)
                        ZoidSetAnim(zoid, anim + next);
                    if (next == 3)
                        mount->state = 4;
                    else
                        mount->state = 0;
                    if (cur == WEAPON_MOUNT_SUPER_ATTACK && mount->state == 4)
                        mount->state = 0;
                }
            }
        }
        if (cur == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
            off = 0;
            for (i = 0; i < 10; i++) {
                if (zdWeaponWpOFF(zoid, &zoid->weapon_mounts[i]) != 0)
                    off = 1;
            }
            if (off != 0)
                return;
        }
        if (zdWeaponWpOFF(zoid, mount) == 0 && state == 0) {
            if (cur == WEAPON_MOUNT_SUPER_ATTACK) {
                zoid->face_lock = 0;
                zoid->requested_action = 0;
            }
            zoid->weapon_mount = want;
        }
        return;
    }
    zdSearchSight(zoid, zoid->weapon_mount);
    if (cur == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
        for (i = 0; i < 10; i++)
            zdSearchSight(zoid, i);
    }
    if (kind == 2) {
        mode = zoid->current_animation;
        if (mode == 2)
            mode = 1;
        if (state == 0 && (mode != 1 || zoid->forward_speed > 0.1 || zoid->field_1A74 > 0.1)) {
            return;
        }
        zoid->field_11E4 = 1;
        if (zoid->requested_action == ZOID_ACTION_ATTACK_0)
            zoid->requested_action = 0;
        if (zoid->requested_action >= ZOID_ACTION_STEP_0 && zoid->requested_action <= ZOID_ACTION_STEP_3)
            zoid->requested_action = 0;
        if (zoid->requested_action == ZOID_ACTION_JUMP_2)
            zoid->requested_action = 0;
    }
    zdWeaponWpON(zoid, mount);
    if (cur == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
        for (i = 0; i < 10; i++)
            zdWeaponWpON(zoid, &zoid->weapon_mounts[i]);
    }
    if (target == NULL)
        mount->state = 2;
    if (state == 2) {
        if ((u32)(type - 3) <= 1) {
            off = 0;
            if (zoid->jump_phase != 0)
                off = 1;
            action = zoid->action;
            if (action == ZOID_ACTION_STEP_3)
                off = 1;
            if (action == ZOID_ACTION_STEP_2)
                off = 1;
            if (action == ZOID_ACTION_STEP_0)
                off = 1;
            if (action == ZOID_ACTION_STEP_1)
                off = 1;
            if (off != 0)
                return;
        }
        if (cur == WEAPON_MOUNT_SUPER_ATTACK) {
            if (zoid->super_attack_input == 0) {
                zoid->super_attack_cooldown = 600;
                zdWeaponFire1(zoid);
                mount->state = 3;
                TEA_VoiceOn(zoid->person, 6);
                return;
            }
            zdWeaponFireOFF(zoid);
        }
    }
    if (state == 3 || state == 5) {
        if (target != NULL) {
            end = zdGetAnimNum(zoid, target);
            if (kind == 2)
                end = zoid->current_animation;
            if (end != anim + 2) {
                if (kind == 1)
                    ZoidSetAnimAllPoint(zoid, target, anim + 2);
                if (kind == 2)
                    ZoidSetAnim(zoid, anim + 2);
                return;
            }
        }
        if (state == 3) {
            if (cur == WEAPON_MOUNT_SUPER_ATTACK)
                zoid->selected_weapon_mount = -1;
            return;
        }
        end = 0;
        if (kind == 2)
            end = zoid->animation_looped;
        if (kind == 1)
            end = getEndFA(target);
        if (end != 0)
            mount->state = 6;
    }
    if (mount->state == 6) {
        if (kind == 1)
            ZoidSetAnimAllPoint(zoid, target, anim + 1);
        if (kind == 2)
            ZoidSetAnim(zoid, anim + 1);
        mount->state = 2;
        state = 2;
    }
    kind = wpTbl[ctl->field_0140[cur]][state];
    if (state < 2 || state == 4) {
        end = 0;
        if (kind == 2)
            end = zoid->animation_looped;
        if (kind == 1)
            end = getEndFA(target);
        if (end != 0 || state == 0) {
            if (kind == 1)
                ZoidSetAnimAllPoint(zoid, target, anim + state);
            if (kind == 2)
                ZoidSetAnim(zoid, anim + state);
            mount->state++;
        }
        return;
    }
    mount->state = 2;
}
