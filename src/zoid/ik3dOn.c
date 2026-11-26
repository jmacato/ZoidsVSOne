#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 zdColPosY(f32 *point, u16 *selector);

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

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void ik3dOn(ZoidState *zoid, FootJoint *foot)
{
    HSD_JObj *joint;
    f32 offset;
    f32 y;
    Vec3 point;
    u16 selector;
    f32 (*matrix)[4];

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    joint = foot->joint;
    if (joint == 0) {
        return;
    }
    matrix = joint->matrix;
    offset = foot->offset;
    point.x = matrix[0][3];
    point.y = foot->height - offset;
    point.z = matrix[2][3];
    y = zdColPosY(&point.x, &selector);
    foot->ground_polygon_index = selector;
    foot->ground = y;
    if (zoid->death_pending == 0) {
        matrix[1][3] = (y + offset) - 10.0f;
        foot->depth = 0.0f;
        HSD_JObjSetTranslateX(foot->joint, 0.0f);
        sGlobal2Local(foot->joint);
    }
}
