#include "zoid.h"
#include "game_camera.h"
#include "model_archive.h"
#include "matrix.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USE_QUATERNION 0x20000

extern ModelArchive *dspRader;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern struct HSD_TObj *searchTObjN(HSD_JObj *joint, s32 *index);
extern void texScrollMtx(struct HSD_TObj *tobj, Mtx matrix);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern ModelArchive *dspPoint;
extern s32 nowStage;
extern s32 radarLen[];
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *condition);

#pragma readonly_strings on
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40))
        result = 1;
    return result;
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

static inline void HSD_JObjAddTranslationX(HSD_JObj *jobj, f32 x)
{
    if (jobj == NULL)
        __assert("jobj.h", 1109, "jobj");
    jobj->translation.x += x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjAddTranslationY(HSD_JObj *jobj, f32 y)
{
    if (jobj == NULL)
        __assert("jobj.h", 1120, "jobj");
    jobj->translation.y += y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, f32 z)
{
    if (jobj == NULL)
        __assert("jobj.h", 716, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[2] = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void s1pRaderMapZoid(ZoidState *zoid, s32 kind, HSD_JObj *joint)
{
    f32 d;
    HSD_JObj *point;
    f64 scale;
    s32 unused[2];
    f32 z;
    f32 x;
    HSD_JObj *child;

    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    if (zoid->death_started != 0)
        return;
    if (zoid->option_active == 2)
        return;
    if (dspRader == NULL)
        return;
    child = GetChild(dspRader->models[0], 0, 1, -1, -1, -1);
    scale = HSD_JObjGetScaleX(joint);
    point = GetChild(dspPoint->models[0], 0, kind, -1, -1, -1);
    jobjCopyPos(child, point);
    x = zoid->position[0];
    z = zoid->position[2];
    if (point == NULL)
        return;
    d = scale * (12.8 * (x / radarLen[nowStage]));
    HSD_JObjAddTranslationX(point, d);
    d = scale * (12.8 * (-z / radarLen[nowStage]));
    HSD_JObjAddTranslationY(point, d);
    d = 3.1415926 + zoid->heading;
    HSD_JObjSetRotationZ(point, d);
    HSD_JObjDisp(point, 0, 7, 0);
}

extern f64 __frsqrte(f64);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sCameraRela(CameraState *camera, Vec3 *point, Vec3 *out);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

void s1pRaderBattleZoid(CameraState *camera, ZoidState *zoid, s32 kind, HSD_JObj *base)
{
    ZoidState *target;
    HSD_JObj *child;
    HSD_JObj *point;
    HSD_JObj *joint;
    Vec3 rel;
    Vec3 pos;
    f32 scale;
    f32 len;
    f32 range;
    f32 x;
    s32 unused[1];
    volatile f32 root;
    f32 z;
    s32 unused2[3];

    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    if (zoid->death_started != 0)
        return;
    if (kind != 0 && zoid->option_active == 2)
        return;
    target = camera->zoid;
    if (target == NULL)
        return;
    if (target->joint == NULL)
        return;
    if (dspPoint == NULL)
        return;
    if (dspRader == NULL)
        return;
    child = GetChild(dspRader->models[0], 0, 1, -1, -1, -1);
    point = GetChild(dspPoint->models[0], 0, kind, -1, -1, -1);
    scale = HSD_JObjGetScaleX(base);
    jobjCopyPos(child, point);
    sMakeMatrix(point);
    joint = zoid->head_coobj.joint;
    if (joint == NULL)
        joint = zoid->bust_coobj.joint;
    if (joint == NULL)
        joint = zoid->neck_coobj.joint;
    if (joint == NULL)
        joint = zoid->hip_coobj.joint;
    if (joint == NULL)
        joint = zoid->buckle_joint;
    if (joint == NULL)
        joint = zoid->joint;
    pos.x = joint->matrix[0][3];
    pos.y = joint->matrix[1][3];
    pos.z = joint->matrix[2][3];
    sCameraRela(camera, &pos, &rel);
    z = rel.z;
    x = rel.x;
    len = sqrtf(x * x + z * z, &root);
    if (target->radar_range < 0.1)
        target->radar_range = 0.1f;
    range = target->radar_range;
    if (range < len)
        return;
    if (point == NULL)
        return;
    HSD_JObjAddTranslationX(point, scale * (11.2 * (x / range / 2.0f)));
    HSD_JObjAddTranslationY(point, scale * (11.2 * (z / range / 2.0f)));
    HSD_JObjSetRotationZ(point, zoid->heading - camera->yaw);
    HSD_JObjDisp(point, 0, 7, 0);
}
#pragma readonly_strings off

void s1pRaderMap(ZoidState *zoid, HSD_JObj *joint, HSD_JObj *base)
{
    s32 index;
    Mtx matrix;
    HSD_JObj *child;
    struct HSD_TObj *tobj;
    ZoidState *other;
    s32 i;

    if (dspRader == 0)
        return;
    jobjCopyPosS(joint, dspRader->models[0]);
    child = GetChild(dspRader->models[0], 0, 1, -1, -1, -1);
    index = 0;
    tobj = searchTObjN(child, &index);
    PSMTXTrans(matrix, 0.0f, 0.0f, 0.0f);
    texScrollMtx(tobj, matrix);
    HSD_JObjDisp(child, 0, 7, 0);
    s1pRaderMapZoid(zoid, 0, base);
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (zoid == other)
            continue;
        if (other->joint == 0)
            continue;
        s1pRaderMapZoid(other, zoid->slot == other->slot ? 3 : 1, base);
    }
}

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

extern void jobjDisp(HSD_JObj *joint);

#pragma readonly_strings on
void s1pRaderBattle(CameraState *camera, ZoidState *zoid, HSD_JObj *joint, HSD_JObj *base)
{
    ZoidState *other;
    HSD_JObj *root;
    HSD_JObj *child;
    f32 value;
    f32 scale;
    s32 i;
    s32 kind;

    if (dspRader == 0)
        return;
    jobjCopyPosS(joint, dspRader->models[0]);
    sMakeMatrix(dspRader->models[0]);
    root = dspRader->models[0];
    child = GetChild(root, 0, 0, -1, -1, -1);
    HSD_JObjDisp(child, 0, 7, 0);
    child = GetChild(dspRader->models[0], 0, 0, 0, -1, -1);
    value = 3.1415926 + -camera->yaw;
    HSD_JObjSetRotationZ(child, value);
    HSD_JObjDisp(child, 0, 7, 0);
    if (zoid->radar_range > 0.0f) {
        child = GetChild(root, 0, 0, 2, -1, -1);
        if (child != 0) {
            scale = zoid->search_range / zoid->radar_range;
            value = scale;
            if (scale > 1.0f)
                value = 1.0f;
            HSD_JObjSetScaleX(child, value);
            HSD_JObjSetScaleY(child, value);
            sMakeMatrix(child);
            jobjDisp(child);
        }
    }
    s1pRaderBattleZoid(camera, zoid, 0, base);
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (zoid != other && other->joint != 0) {
            if (zoid->slot == other->slot)
                kind = 3;
            else
                kind = 1;
            s1pRaderBattleZoid(camera, other, kind, base);
        }
    }
}
#pragma readonly_strings off

void s1pRader(CameraState *camera, ZoidState *zoid, HSD_JObj *joint)
{
    ZoidState *other;
    s32 found;
    s32 i;

    found = 0;
    if (dspRader == 0)
        return;
    joint = GetChild(joint, 0, 5, -1, -1, -1);
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other == zoid)
            continue;
        if (other->joint == 0)
            continue;
        if (other->death_started != 0)
            continue;
        if (zoid->slot == other->slot)
            continue;
        if (zoid->distances[i] < zoid->radar_range) {
            found = 1;
            break;
        }
    }
    if (found != 0)
        s1pRaderBattle(camera, zoid, joint, joint);
    else
        s1pRaderMap(zoid, joint, joint);
}
