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
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void jobjDispAll(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern s32 sprintf(char *buffer, const char *format, ...);

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

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void s1pTarget(CameraState *camera, ZoidState *zoid)
{
    HSD_JObj *joint;
    HSD_JObj *lock0;
    HSD_JObj *lock1;
    HSD_JObj *lock2;
    HSD_JObj *bar;
    ZoidState *other;
    s32 i;
    s32 flags;
    s32 pt[2];
    Vec3 pos;
    s32 slot;
    char *text;
    f32 x;
    f32 y;
    f32 ratio;
    HSD_JObj *digit;
    char buf[12];
    s32 unused[2];

    if (dsp1p == NULL)
        return;
    slot = zoid->slot;
    lock0 = GetChild(dsp1p->models[14], 0, 0, -1, -1, -1);
    lock1 = GetChild(dsp1p->models[14], 0, 1, -1, -1, -1);
    lock2 = GetChild(dsp1p->models[14], 0, 2, -1, -1, -1);
    bar = dsp1p->models[16];
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other->joint == NULL)
            continue;
        if (other == zoid)
            continue;
        if (other->stel_state == ZOID_STEL_ON)
            continue;
        if (slot == other->slot)
            continue;
        flags = 0;
        joint = other->camera_joint;
        pos.x = joint->matrix[0][3];
        pos.y = joint->matrix[1][3];
        pos.z = joint->matrix[2][3];
        if (sCameraPt2d(camera, &pos, pt) == 0)
            continue;
        if (zoid->attack_in_range[i] == 1)
            flags |= 4;
        x = (pt[0] - 320) / 10.0;
        y = (240 - pt[1]) / 10.0;
        if (flags != 0) {
            HSD_JObjSetTranslateX(lock0, x);
            HSD_JObjSetTranslateY(lock0, y);
            HSD_JObjSetTranslateX(lock1, x);
            HSD_JObjSetTranslateY(lock1, y);
            HSD_JObjSetTranslateX(lock2, x);
            HSD_JObjSetTranslateY(lock2, y);
            if (flags & 1)
                HSD_JObjDisp(lock0, 0, 7, 0);
            if (flags & 2)
                HSD_JObjDisp(lock1, 0, 7, 0);
            if (flags & 4)
                HSD_JObjDisp(lock2, 0, 7, 0);
        }
        if (other->health_bar_timer == 0)
            continue;
        HSD_JObjSetTranslateX(bar, 2.0f + x);
        HSD_JObjSetTranslateY(bar, y - 2.0f);
        ratio = (f32)other->health / (f32)other->max_health;
        HSD_JObjSetScaleX(GetChild(bar, 0, 1, -1, -1, -1), ratio);
        sMakeMatrix(bar);
        jobjDispAll(bar);
        sprintf(buf, "%04d", other->health);
        text = buf;
        for (flags = 0; flags < 4; flags++, text++) {
            digit = GetChild(dsp1p->models[12], 0, 0, *text - '0', -1, -1);
            jobjCopyPos(GetChild(bar, 0, 0, flags, -1, -1), digit);
            jobjDispAll(digit);
        }
    }
}
