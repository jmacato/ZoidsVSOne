/* SDK setters follow
 * https://github.com/doldecomp/melee/blob/master/src/sysdolphin/baselib/jobj.h. */
#include "jobj.h"
#include "zoid.h"

#pragma auto_inline off
#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USE_QUATERNION 0x00020000
#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !matrix_is_dirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 696, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 676, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[0] = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void zdSetXYZ(ZoidState *zoid)
{
    HSD_JObjSetTranslateX(zoid->joint, zoid->position[0]);
    HSD_JObjSetTranslateY(zoid->joint, zoid->position[1] + zoid->height_offset);
    HSD_JObjSetTranslateZ(zoid->joint, zoid->position[2]);
    HSD_JObjSetRotationY(zoid->joint, zoid->heading);
    HSD_JObjSetRotationX(zoid->joint, zoid->pitch);
}

void zdClearAnimRy(HSD_JObj *joint, u32 flags)
{
    if (joint != 0 && (joint = joint->child) != 0) {
        if (flags & 4)
            HSD_JObjSetRotationY(joint, 0.f);
        if (flags & 0x10)
            HSD_JObjSetTranslateY(joint, 0.f);
        if (flags & 0x20)
            HSD_JObjSetTranslateX(joint, 0.f);
        if (flags & 0x40)
            HSD_JObjSetTranslateZ(joint, 0.f);
    }
}
