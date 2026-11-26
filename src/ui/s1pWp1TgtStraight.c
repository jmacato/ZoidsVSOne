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
/* the definition also takes f32 distance; the original call passes only 2 arguments */
extern s32 sWeaponGetBarrel(WeaponState *weapon, Vec3 *position);

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

void s1pWp1TgtStraight(CameraState *camera, WeaponState *weapon)
{
    HSD_JObj *jobj;
    HSD_JObj *target_joint;
    HSD_JObj *lock;
    ZoidState *owner;
    ZoidState *target;
    s32 i;
    f32 x;
    f32 y;
    s32 pad_top[2];
    Vec3 position;
    s32 pad_mid[3];
    s32 pt[2];
    s32 pad0;
    f32 diff;
    s32 unused[3];

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
    if (sWeaponGetBarrel(weapon, &position) == 0)
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
