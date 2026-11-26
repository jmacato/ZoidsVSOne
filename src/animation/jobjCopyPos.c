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

void jobjCopyPos(HSD_JObj *source, HSD_JObj *joint)
{
    f32 x;
    f32 y;
    f32 z;

    if (joint == 0)
        return;
    if (source == 0)
        return;
    x = source->matrix[0][3];
    joint->matrix[0][3] = x;
    y = source->matrix[1][3];
    joint->matrix[1][3] = y;
    z = source->matrix[2][3];
    joint->matrix[2][3] = z;
    HSD_JObjSetScaleX(joint, 1.0f);
    sGlobal2Local(joint);
    HSD_JObjSetMtxDirty(joint);
    sMakeMatrix(joint);
}
