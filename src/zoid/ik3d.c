#include "zoid.h"
#include "ground_collision.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void PSMTXRotRad(f32 m[3][4], s8 axis, f32 rad);
extern void PSMTXMultVecSR(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern void PSMTXConcat(f32 a[3][4], f32 b[3][4], f32 ab[3][4]);

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

static inline f32 HSD_JObjGetTranslationY(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 1021, "jobj");
    return jobj->translation.y;
}

static inline void HSD_JObjCheck(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 762, "jobj");
}

static inline f32 fabsf(f32 *v)
{
    return (*(u32 *)v &= 0x7FFFFFFF, *v);
}

void ik3d(ZoidState *zoid, FootJoint *foot)
{
    Vec3 point;
    f32 pad0[4];
    u16 selector;
    f32 pad1[2];
    Vec3 normal;
    Vec3 front;
    f32 m[3][4];
    f32 diff;
    f32 (*mtx)[4];
    HSD_JObj *joint;
    Vec3 *n;
    f32 offset;
    f32 y;
    s32 mode;
    s32 hit;
    f32 unused[6];

    hit = 0;
    if (foot == NULL)
        return;
    foot->flags &= ~FOOT_FLAG_CONTACT;
    joint = foot->joint;
    if (joint == NULL)
        return;
    mode = zoid->current_animation;
    if (mode == 2)
        mode = 1;
    offset = foot->offset;
    mtx = joint->matrix;
    HSD_JObjGetTranslationY(joint);
    point.x = mtx[0][3];
    point.y = foot->height - offset;
    point.z = mtx[2][3];
    y = zdColPosY(&point.x, &selector);
    foot->ground_polygon_index = selector;
    foot->ground = y;
    foot->depth = y - point.y;
    if (zoid->death_pending != 0)
        return;
    HSD_JObjCheck(joint);
    if (mode != 1) {
        if (foot->field_2C < 0.0f)
            foot->field_2C += 0.1;
        if (foot->field_2C >= 0.0f)
            foot->field_2C = 0.0f;
    }
    if (y >= point.y)
        hit = 1;
    diff = y - mtx[1][3];
    if (fabsf(&diff) < 0.06)
        hit = 1;
    if (hit == 0) {
        foot->rot_z = 1.0f;
        foot->rot_x = 1.0f;
    }
    foot->no_contact_frames++;
    if (hit != 0) {
        zoid->grounded = 1;
        foot->no_contact_frames = 0;
        mtx[1][3] = 0.002 + (y + offset);
        foot->flags |= FOOT_FLAG_CONTACT | FOOT_FLAG_SUPPORTED;
        if (selector != GROUND_POLYGON_NONE) {
            n = &grdcNormal[grdcPolygon[selector].normal_index];
            zoid->ground_normal_count++;
            zoid->ground_normal_sum[0] += n->x;
            zoid->ground_normal_sum[1] += n->y;
            zoid->ground_normal_sum[2] += n->z;
            normal.x = n->x;
            normal.y = n->y;
            normal.z = n->z;
            front.x = mtx[0][1];
            front.y = mtx[1][1];
            front.z = mtx[2][1];
            PSMTXRotRad(m, 'Y', -zoid->heading);
            PSMTXMultVecSR(m, &normal, &normal);
            PSMTXMultVecSR(m, &front, &front);
            if (normal.x < front.x) {
                if (foot->rot_z < 0.0f)
                    foot->rot_z = -0.95 * foot->rot_z;
                if (foot->rot_z < 0.001)
                    foot->rot_z = 0.001f;
                PSMTXRotRad(m, 'Z', 0.017453292f * foot->rot_z);
                PSMTXConcat(mtx, m, mtx);
            }
            if (normal.x > front.x) {
                if (foot->rot_z > 0.0f)
                    foot->rot_z = -0.95 * foot->rot_z;
                if (foot->rot_z > -0.001)
                    foot->rot_z = -0.001f;
                PSMTXRotRad(m, 'Z', 0.017453292f * foot->rot_z);
                PSMTXConcat(mtx, m, mtx);
            }
            if (normal.z > front.z) {
                if (foot->rot_x < 0.0f)
                    foot->rot_x = -0.95 * foot->rot_x;
                if (foot->rot_x < 0.001)
                    foot->rot_x = 0.001f;
                PSMTXRotRad(m, 'X', 0.017453292f * foot->rot_x);
                PSMTXConcat(mtx, m, mtx);
            }
            if (normal.z < front.z) {
                if (foot->rot_x > 0.0f)
                    foot->rot_x = -0.95 * foot->rot_x;
                if (foot->rot_x > -0.001)
                    foot->rot_x = -0.001f;
                PSMTXRotRad(m, 'X', 0.017453292f * foot->rot_x);
                PSMTXConcat(mtx, m, mtx);
            }
            foot->field_14 = 0.0f;
            foot->field_18 = 0.0f;
        }
        HSD_JObjSetTranslateX(joint, 0.0f);
        sGlobal2Local(joint);
    } else {
        if (mtx[1][3] > point.y + zoid->senter_translation_y) {
            mtx[1][3] = point.y + zoid->senter_translation_y;
            HSD_JObjSetTranslateX(joint, 0.0f);
            sGlobal2Local(joint);
        }
    }
    if (foot->no_contact_frames > 15) {
        if (foot->no_contact_frames > 600)
            foot->no_contact_frames = 600;
        foot->flags &= ~FOOT_FLAG_SUPPORTED;
    }
}
