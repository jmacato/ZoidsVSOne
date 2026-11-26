#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern f32 sColPosY(Vec3 *point, u16 *selector);
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

f32 zdDownBody(ZoidState *zoid, CoObj *co)
{
    Vec3 position;
    s32 frame_padding[3];
    f32 radius;
    f32 depth;

    if (zoid == 0) {
        return 0.0f;
    }
    if (zoid->joint == 0) {
        return 0.0f;
    }
    if (co == 0) {
        return 0.0f;
    }
    if (co->joint == 0) {
        return 0.0f;
    }
    if (co->base_joint == 0) {
        return 0.0f;
    }
    radius = co->minimum_scale;
    position.x = co->base_joint->matrix[0][3];
    position.y = co->base_joint->matrix[1][3];
    position.z = co->base_joint->matrix[2][3];
    depth = sColPosY(&position, 0) - (position.y - radius);
    if (depth < -0.1) {
        depth = -0.1f;
    }
    co->base_joint->matrix[1][3] += depth;
    sGlobal2Local(co->base_joint);
    HSD_JObjSetScaleX(co->base_joint, 1.0f);
    HSD_JObjSetScaleY(co->base_joint, 1.0f);
    HSD_JObjSetScaleZ(co->base_joint, 1.0f);
    if (depth >= 0.01) {
        return depth;
    }
    return 0.0f;
}
