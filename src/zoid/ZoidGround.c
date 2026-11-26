#include "zoid.h"
#include "ground_collision.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern Vec3 CubeTBL[9];
extern void PSMTXMultVecArray(f32 m[3][4], Vec3 *src, Vec3 *dst, u32 count);
extern s32 zdGroundTBL(ZoidState *zoid, u16 *table);
extern void ZoidCoObjMtxI(ZoidState *zoid);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sLinier3d(Vec3 *current, Vec3 *target, f32 fraction);
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

static inline void PAD_STACK(void)
{
    s32 frame_padding[6];
    frame_padding[0] = 0;
}

s32 ZoidGround(ZoidState *zoid)
{
    u16 *tables[9];
    Vec3 points[9];
    s32 pad[1];
    u16 *table;
    CoObj *co;
    Vec3 joint;
    s32 i;
    s32 count;
    Vec3 base;
    s32 unused[4];
    f32 z;
    f32 original;
    s32 hit;
    HSD_JObj *child;
    s32 flag;
    s32 j;

    flag = 0;
    if (zoid == 0) {
        return 0;
    }
    co = &zoid->body_coobj;
    if (co->joint == 0) {
        return 0;
    }
    PSMTXMultVecArray(co->joint->matrix, CubeTBL, points, 9);
    count = 0;
    for (i = 0; i < 9; i++) {
        table = sColPosTBL(&points[i]);
        if (table != 0) {
            for (j = 0; j < count; j++) {
                if (tables[j] == table) {
                    break;
                }
            }
            if (j == count) {
                tables[count] = table;
                count++;
            }
        }
    }
    if (count == 0) {
        return 0;
    }
    for (j = count; j < 9; j++) {
        tables[j] = 0;
    }
    ZoidCoObjMtxI(zoid);
    hit = 0;
    for (j = 0; j < count; j++) {
        if (tables[j] != 0 && zdGroundTBL(zoid, tables[j]) != 0) {
            hit = 1;
        }
    }
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    joint.x = zoid->sweep_joint->matrix[0][3];
    base.x = zoid->sweep_origin[0];
    joint.y = zoid->sweep_joint->matrix[1][3];
    base.y = zoid->sweep_origin[1];
    joint.z = zoid->sweep_joint->matrix[2][3];
    base.z = zoid->sweep_origin[2];
    zoid->sweep_hit = 0;
    z = sColPt(&base, &joint, (GroundMask){{255, 0, 0, 0}});
    PAD_STACK();
    if (GROUND_NO_HIT != z) {
        sLinier3d(&base, &joint, z);
        zoid->sweep_hit = 1;
        zoid->field_1A74 = 0.0f;
        zoid->ramped_speed = 0.0f;
        zoid->forward_speed = 0.0f;
    }
    if (zoid->sweep_hit != 0) {
        flag = 1;
    }
    if (zoid->head_coobj.ground_contact & 1) {
        flag = 1;
    }
    if (flag != 0) {
        child = zoid->joint->child;
        if (child != 0) {
            z = HSD_JObjGetTranslationZ(child);
            original = z;
            if (z > 0.3) {
                z -= 0.2;
            }
            if (z > 1.0f) {
                z -= 1.0f;
            }
            if (z < -0.3) {
                z += 0.2;
            }
            if (z < -1.0f) {
                z += 1.0f;
            }
            if (z != original) {
                HSD_JObjSetTranslateZ(child, z);
            }
        }
    }
    zdSetXYZ(zoid);
    return hit;
}
