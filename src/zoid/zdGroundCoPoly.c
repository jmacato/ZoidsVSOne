#include "zoid.h"
#include "ground_collision.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern s32 zdGrdCoPo00(CoObj *object, GroundPolygon *polygon);
extern f32 sLenPoint3d(Vec3 *a, Vec3 *b);
extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern void sLinier3d(f32 *current, f32 *target, f32 fraction);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void zdSetXYZ(ZoidState *zoid);
extern void sGlobal2Local(HSD_JObj *joint);
extern u32 PSMTXInverse(f32 src[3][4], f32 dst[3][4]);
extern f32 zdCoGrdRot(ZoidState *zoid, HSD_JObj **joint, f32 *direction, s32 scale);
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

static inline GroundMask zdGroundMask(void)
{
    GroundMask a;
    GroundMask b;
    GroundMask c;
    GroundMask d;

    a = (GroundMask){{255, 0, 0, 0}};
    b = a;
    c = b;
    d = c;
    return d;
}

s32 zdGroundCoPoly(ZoidState *zoid, CoObj *object, s32 index, GroundPolygon *polygon, s32 mode)
{
    u8 unused0[4];
    f32 pos[3];
    f32 line[3];
    f32 cur[3];
    f32 prev[3];
    f32 back[3];
    f32 top[3];
    f32 test[3];
    u8 unused1[4];
    f32 len;
    f32 dist;
    f32 diff;
    f32 rate;
    s32 i;
    s32 k;
    Vec3 *normal;

    if (object->joint == 0)
        return 0;
    if (object->base_joint == 0)
        return 0;
    len = GROUND_NO_HIT;
    pos[0] = object->joint->matrix[0][3];
    pos[1] = object->joint->matrix[1][3];
    pos[2] = object->joint->matrix[2][3];
    if (zdGrdCoPo00(object, polygon) == 0) {
        if (zoid->current_animation > 2)
            len = sColPt00((Vec3 *)object->position, (Vec3 *)pos, polygon, zdGroundMask());
        if (GROUND_NO_HIT != len) {
            dist = sLenPoint3d((Vec3 *)object->position, (Vec3 *)pos);
            if (dist > 0.0f)
                len -= object->minimum_scale / dist;
        }
        if (GROUND_NO_HIT == len)
            return 0;
        if (mode == 0)
            return 1;
        for (i = 0; i < 3; i++) {
            line[i] = sLiner(pos[i], object->position[i], len);
            dist = pos[i] - line[i];
            diff = dist;
            if (mode == 1)
                diff = 0.02 * dist;
            if (mode == 3 && i == 1)
                continue;
            if (mode < 2)
                continue;
            zoid->position[i] -= diff;
        }
        sGlobal2Local(object->base_joint);
        HSD_JObjSetScaleX(object->base_joint, 1.0f);
        HSD_JObjSetScaleY(object->base_joint, 1.0f);
        HSD_JObjSetScaleZ(object->base_joint, 1.0f);
        zdSetXYZ(zoid);
        return 1;
    }
    object->ground_polygon_index = index;
    object->ground_contact |= 1;
    if (mode == 0)
        return 1;
    zoid->grounded = 1;
    normal = &grdcNormal[polygon->normal_index];
    if (mode == 2 || mode == 3) {
        for (i = 0; i < 3; i++) {
            cur[i] = zoid->position[i];
            prev[i] = zoid->previous_position[i];
            top[i] = object->joint->matrix[i][3];
        }
        for (k = 0; k < 10; k++) {
            dist = 0.1 * (10 - k);
            for (i = 0; i < 3; i++) {
                back[i] = prev[i];
                test[i] = top[i];
            }
            sLinier3d(back, cur, dist);
            for (i = 0; i < 3; i++)
                test[i] -= cur[i] - back[i];
            if (!(zdColPosY(test, NULL) > test[1]))
                break;
        }
        for (i = 0; i < 3; i++)
            zoid->position[i] = back[i];
        zdSetXYZ(zoid);
    }
    if (object->base_joint != 0) {
        for (k = 0; k < 40; k++) {
            object->base_joint->matrix[0][3] += 0.2f * normal->x;
            object->joint->matrix[0][3] += 0.2f * normal->x;
            object->base_joint->matrix[1][3] += 0.2f * normal->y;
            object->joint->matrix[1][3] += 0.2f * normal->y;
            object->base_joint->matrix[2][3] += 0.2f * normal->z;
            object->joint->matrix[2][3] += 0.2f * normal->z;
            PSMTXInverse(object->joint->matrix, object->inverse);
            if (zdGrdCoPo00(object, polygon) == 0)
                break;
        }
        sGlobal2Local(object->base_joint);
        HSD_JObjSetScaleX(object->base_joint, 1.0f);
        HSD_JObjSetScaleY(object->base_joint, 1.0f);
        HSD_JObjSetScaleZ(object->base_joint, 1.0f);
    }
    zoid->ground_turn += zdCoGrdRot(zoid, &object->joint, &normal->x, k);
    rate = 0.07f;
    if (mode <= 1)
        rate = 0.001f;
    for (i = 0; i < 3; i++) {
        if (i == 1 && mode == 3)
            continue;
        zoid->joint->matrix[i][3] += (f32)k * (rate * (&normal->x)[i]) / 2.0f;
        zoid->position[i] += (f32)k * (rate * (&normal->x)[i]) / 2.0f;
    }
    if (mode >= 2) {
        for (i = 0; i < 3; i++) {
            if (i == 1)
                continue;
            diff = 0.3 * (zoid->joint->child->matrix[i][3] - zoid->pose->child->matrix[i][3]);
            zoid->position[i] -= diff;
            zoid->joint->matrix[i][3] -= diff;
        }
    }
    zdSetXYZ(zoid);
    return 1;
}
