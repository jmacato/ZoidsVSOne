#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
#define JOBJ_USE_QUATERNION 0x20000

static const char s804[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

extern void __assert(const char *file, s32 line, const char *expr);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void zdFace(ZoidState *zoid);

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
        __assert("jobj.h", 697, s804);
    jobj->rotation[1] = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, f32 x)
{
    if (jobj == NULL)
        __assert("jobj.h", 676, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 677, s804);
    jobj->rotation[0] = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void ZoidSiseiFace(ZoidState *zoid)
{
    f32 angle;
    s32 frame_padding[2];

    zdFace(zoid);
    angle = zoid->face_yaw;
    if (angle) {
        HSD_JObjSetRotationY(zoid->buckle_joint, 8.0 * angle / 53.0);
        HSD_JObjSetRotationY(zoid->jacket_joint, 20.0 * angle / 53.0);
        HSD_JObjSetRotationY(zoid->collar_joint, 25.0 * angle / 53.0);
    }
    angle = zoid->face_pitch;
    if (angle) {
        HSD_JObjSetRotationX(zoid->buckle_joint, 8.0 * angle / 53.0);
        HSD_JObjSetRotationX(zoid->jacket_joint, 20.0 * angle / 53.0);
        HSD_JObjSetRotationX(zoid->collar_joint, 25.0 * angle / 53.0);
    }
}
