#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void sLinier3d(f32 *current, f32 *target, f32 fraction);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY))
        result = 1;
    return result;
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetScaleY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 819, "jobj");
    jobj->scale.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetScaleZ(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 833, "jobj");
    jobj->scale.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void ZoidTo(ZoidState *zoid, ZoidLimb *limb, s32 ground)
{
    HSD_JObj *joint;
    f32 y;
    f32 *position;
    u8 frame_padding[0x28];

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    if (limb == 0) {
        return;
    }
    joint = limb->joint;
    if (joint == 0) {
        return;
    }
    limb->position[0] = joint->matrix[0][3];
    limb->position[1] = joint->matrix[1][3];
    limb->position[2] = joint->matrix[2][3];
    position = limb->position;
    if (ground != 0) {
        y = zdColPosY(position, 0);
        if (position[1] < y) {
            position[1] = y;
        }
    }
    joint->matrix[0][3] = limb->position[0];
    joint->matrix[1][3] = limb->position[1];
    joint->matrix[2][3] = limb->position[2];
    sGlobal2Local(joint);
    HSD_JObjSetScaleX(joint, 1.0f);
    HSD_JObjSetScaleY(joint, 1.0f);
    HSD_JObjSetScaleZ(joint, 1.0f);
}

void ZoidToF(ZoidLimb *limb, ZoidLimb *target, f32 rate)
{
    HSD_JObj *joint;
    HSD_JObj *target_joint;
    u8 frame_padding[0x10];

    if (limb == 0) {
        return;
    }
    if (target == 0) {
        return;
    }
    joint = limb->joint;
    target_joint = target->joint;
    if (joint == 0) {
        return;
    }
    if (target_joint == 0) {
        return;
    }
    sLinier3d(limb->position, target->position, rate);
    joint->matrix[0][3] = limb->position[0];
    joint->matrix[1][3] = limb->position[1];
    joint->matrix[2][3] = limb->position[2];
    sGlobal2Local(joint);
    HSD_JObjSetScaleX(joint, 1.0f);
    HSD_JObjSetScaleY(joint, 1.0f);
    HSD_JObjSetScaleZ(joint, 1.0f);
}

void ZoidToDownF(ZoidLimb *limb, ZoidLimb *target, f32 rate)
{
    HSD_JObj *joint;
    HSD_JObj *target_joint;
    u8 frame_padding[0x8];

    if (limb == 0) {
        return;
    }
    if (target == 0) {
        return;
    }
    joint = limb->joint;
    target_joint = target->joint;
    if (joint == 0) {
        return;
    }
    if (target_joint == 0) {
        return;
    }
    target->position[1] = zdColPosY(target->position, 0);
    sLinier3d(limb->position, target->position, rate);
    joint->matrix[0][3] = limb->position[0];
    joint->matrix[1][3] = limb->position[1];
    joint->matrix[2][3] = limb->position[2];
    sGlobal2Local(joint);
    HSD_JObjSetScaleX(joint, 1.0f);
    HSD_JObjSetScaleY(joint, 1.0f);
    HSD_JObjSetScaleZ(joint, 1.0f);
}
