#include "weapon.h"
#include "joint_matrix.h"
#include "zoid.h"
#include "aobj.h"

#define NULL 0

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void *getAnimAobj(HSD_JObj *joint);
extern u32 HSD_AObjGetFlags(void *aobj);
extern void PSMTXInverse(f32 src[3][4], f32 inv[3][4]);
extern void sWeaponTarget(WeaponState *weapon, HSD_JObj *target);
extern void sWeaponSight(WeaponState *weapon);
extern void sWeaponTrace(WeaponState *weapon);
extern void sWeaponFire(WeaponState *weapon);

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !matrix_is_dirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

void sWeaponMove(WeaponState *weapon)
{
    HSD_JObj *mount;
    HSD_JObj *joint;
    HSD_JObj *target_joint;
    ZoidState *owner;
    ZoidState *target;
    void *aobj;
    s32 model;
    s32 i;
    s32 j;

    mount = weapon->mount_joint;
    model = weapon->model;
    if (mount == NULL)
        return;
    joint = weapon->archive->models[model];
    if (joint == NULL)
        return;
    if (weapon->flags & 4)
        return;
    owner = weapon->owner;
    target = NULL;
    target_joint = NULL;
    if (owner != NULL) {
        if (owner->target_pending) {
            target = &Zoid[owner->target_slot];
            if (target->joint == NULL)
                target = NULL;
        }
        if (owner->death_started)
            target = NULL;
    }
    if (target != NULL && target->joint == NULL)
        target = NULL;
    if (target != NULL) {
        target_joint = target->joint;
        if (target->camera_joint != NULL)
            target_joint = target->camera_joint;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            joint->matrix[i][j] = mount->matrix[i][j];
        }
    }
    sGlobal2Local(joint);
    aobj = getAnimAobj(joint);
    if (!(weapon->state_flags & WEAPON_STATE_STOPPED)) {
        HSD_JObjAnimAll(joint);
        weapon->state_flags |= 8;
        if (HSD_AObjGetFlags(aobj) & AOBJ_REWINDED) {
            weapon->state_flags &= ~8;
            if (weapon->flags & WEAPON_FLAG_LOOP_OFF)
                weapon->state_flags |= WEAPON_STATE_STOPPED;
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            joint->matrix[i][j] = mount->matrix[i][j];
        }
    }
    sWeaponTarget(weapon, target_joint);
    sWeaponSight(weapon);
    sWeaponTrace(weapon);
    HSD_JObjSetMtxDirty(joint);
    sMakeMatrix(joint);
    sWeaponFire(weapon);
    for (i = 0; i < 12; i++) {
        if (weapon->inverses[i].joint != NULL)
            PSMTXInverse(weapon->inverses[i].joint->matrix, weapon->inverses[i].inverse);
    }
}
