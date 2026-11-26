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

void s1pWp1TgtHome(CameraState *camera, WeaponState *weapon)
{
    HSD_JObj *normal;
    HSD_JObj *lock;
    HSD_JObj *jobj;
    WeaponMarker *marker;
    ZoidState *target;
    void *source;
    s32 i;
    s32 pt[4];
    f32 x;
    f32 y;

    if (dsp1p == 0)
        return;
    if (weapon == 0)
        return;
    if (weapon->active == 0)
        return;
    normal = GetChild(dsp1p->models[14], 0, 0, -1, -1, -1);
    lock = GetChild(dsp1p->models[14], 0, 1, -1, -1, -1);
    for (i = 0; i < weapon->marker_count; i++) {
        marker = &weapon->markers[i];
        if (marker->joint == 0)
            continue;
        target = marker->target;
        source = marker->source;
        if (target == 0 && source == 0)
            continue;
        if (target != 0 && target->joint != 0 && target->stel_state == ZOID_STEL_ON)
            continue;
        if (sCameraPt2d(camera, &marker->position, pt) == 0) {
            if (marker->locked != 0)
                marker->joint = 0;
            continue;
        }
        jobj = normal;
        if (marker->locked != 0) {
            camera->target_marker_count++;
            jobj = lock;
        }
        x = (pt[0] - 320) / 10.0;
        y = (240 - pt[1]) / 10.0;
        HSD_JObjSetTranslateX(jobj, x);
        HSD_JObjSetTranslateY(jobj, y);
        jobjDisp(jobj);
    }
}
