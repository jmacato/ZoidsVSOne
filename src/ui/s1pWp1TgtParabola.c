#include "jobj.h"
#include "model_archive.h"
#include "game_camera.h"
#include "weapon.h"
#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern ModelArchive *dsp1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 sCameraPt2d(CameraState *camera, Vec3 *position, s32 *screen_point);
extern void jobjDisp(HSD_JObj *joint);
extern s32 sWeaponGetBarrelParabola(WeaponState *weapon, Vec3 *position, f32 distance);
extern f64 __frsqrte(f64);

static inline f32 sqrtf(f32 x)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;
    volatile f32 y;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

static inline f32 fabsf(f32 *value)
{
    return (*(u32 *)value &= 0x7FFFFFFF, *value);
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

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void s1pWp1TgtParabola(CameraState *camera, WeaponState *weapon)
{
    HSD_JObj *jobj;
    HSD_JObj *target_joint;
    HSD_JObj *lock;
    HSD_JObj *barrel;
    ZoidState *owner;
    ZoidState *target;
    s32 i;
    f32 x;
    f32 y;
    f32 dist;
    f32 dx;
    f32 dz;
    f64 guess;
    s32 pad_top[1];
    Vec3 position;
    Vec3 tpos;
    s32 pt[2];
    s32 pad_b[1];
    volatile f32 root;
    f32 diff;
    s32 unused[3];

    (void)&tpos;
    if (dsp1p == 0)
        return;
    if (weapon == 0)
        return;
    if (weapon->active == 0)
        return;
    owner = weapon->owner;
    target_joint = NULL;
    target = NULL;
    if (owner != NULL && owner->target_pending)
        target = &Zoid[owner->target_slot];
    if (target != NULL)
        target_joint = target->camera_joint;
    if (target_joint != NULL) {
        tpos.x = target_joint->matrix[0][3];
        tpos.y = target_joint->matrix[1][3];
        tpos.z = target_joint->matrix[2][3];
        barrel = weapon->archive->models[0];
        dx = tpos.x - barrel->matrix[0][3];
        dz = tpos.z - barrel->matrix[2][3];
        dist = dx * dx + dz * dz;
        if (dist > 0.0f) {
            guess = __frsqrte((f64)dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            guess = 0.5 * guess * (3.0 - guess * guess * dist);
            root = (f32)(dist * guess);
            dist = root;
        }
    }
    if (sWeaponGetBarrelParabola(weapon, &position, dist) == 0)
        return;
    if (sCameraPt2d(camera, &position, pt) == 0)
        return;
    jobj = GetChild(dsp1p->models[14], 0, 0, -1, -1, -1);
    lock = GetChild(dsp1p->models[14], 0, 1, -1, -1, -1);
    x = (pt[0] - 320) / 10.0;
    y = (240 - pt[1]) / 10.0;
    if (target_joint != NULL) {
        for (i = 0; i < 3; i++) {
            diff = target_joint->matrix[i][3] - (&position.x)[i];
            if (fabsf(&diff) > 5.0f)
                break;
        }
        if (i == 3)
            jobj = lock;
    }
    if (jobj == lock)
        camera->target_marker_count++;
    HSD_JObjSetTranslateX(jobj, x);
    HSD_JObjSetTranslateY(jobj, y);
    jobjDisp(jobj);
}
