#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
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

static inline f32 HSD_JObjGetTranslationZ(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 1033, "jobj");
    return jobj->translation.z;
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 z)
{
    if (jobj == NULL)
        __assert("jobj.h", 980, "jobj");
    jobj->translation.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetupMatrix(HSD_JObj *jobj)
{
    if (!jobj || !HSD_JObjMtxIsDirty(jobj))
        return;
    HSD_JObjSetupMatrixSub(jobj);
}

void zdAtkSubForPull2(ZoidState *zoid)
{
    s8 slot;
    f32 z;
    ZoidState *target;
    s32 frame_padding[2];

    if (zoid != 0 && zoid->joint != 0) {
        slot = zoid->attack_target;
        if (slot != -1 && (target = &Zoid[slot])->joint != 0) {
            z = HSD_JObjGetTranslationZ(zoid->joint->child);
            HSD_JObjSetTranslateZ(zoid->joint->child, z * zoid->pull_scale);
            sMakeMatrix(zoid->joint);
            HSD_JObjSetupMatrix(zoid->joint);
        }
    }
}
