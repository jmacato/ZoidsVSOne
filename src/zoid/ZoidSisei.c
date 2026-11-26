#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
#define JOBJ_USE_QUATERNION 0x20000

extern void __assert(const char *file, s32 line, const char *expr);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern void ZoidSiseiFace(ZoidState *zoid);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

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

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 y)
{
    if (jobj == NULL)
        __assert("jobj.h", 696, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 x)
{
    if (jobj == NULL)
        __assert("jobj.h", 952, "jobj");
    jobj->translation.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 y)
{
    if (jobj == NULL)
        __assert("jobj.h", 966, "jobj");
    jobj->translation.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 z)
{
    if (jobj == NULL)
        __assert("jobj.h", 980, "jobj");
    jobj->translation.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void ZoidSisei(ZoidState *zoid)
{
    f32 angle;

    if (zoid->senter_joint != 0) {
        angle = zoid->senter_roll;
        HSD_JObjSetTranslateX(zoid->senter_joint, zoid->senter_translation_y * sinf(angle));
        HSD_JObjSetTranslateY(zoid->senter_joint, zoid->senter_translation_y * cosf(angle));
        HSD_JObjSetTranslateZ(zoid->senter_joint, zoid->senter_translation_z - absf(zoid->senter_translation_y * sinf(angle)));
    }
    if (zoid->f_base_joint != 0) {
        HSD_JObjSetRotationY(zoid->f_base_joint, zoid->f_base_ry);
    }
    ZoidSiseiFace(zoid);
}
