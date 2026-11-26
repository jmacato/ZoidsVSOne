#include "joint.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

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

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

static inline f32 HSD_JObjGetScaleY(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 911, "jobj");
    return jobj->scale.y;
}

static inline f32 HSD_JObjGetScaleZ(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 923, "jobj");
    return jobj->scale.z;
}

void jobjCopyPosS(HSD_JObj *source, HSD_JObj *joint)
{
    Vec3 pos;

    if (joint == 0)
        return;
    if (source == 0)
        return;
    pos.x = source->matrix[0][3];
    joint->matrix[0][3] = pos.x;
    pos.y = source->matrix[1][3];
    joint->matrix[1][3] = pos.y;
    pos.z = source->matrix[2][3];
    joint->matrix[2][3] = pos.z;
    sGlobal2Local(joint);
    HSD_JObjSetScaleX(joint, HSD_JObjGetScaleX(source));
    HSD_JObjSetScaleY(joint, HSD_JObjGetScaleY(source));
    HSD_JObjSetScaleZ(joint, HSD_JObjGetScaleZ(source));
    HSD_JObjSetMtxDirty(joint);
    sMakeMatrix(joint);
}
