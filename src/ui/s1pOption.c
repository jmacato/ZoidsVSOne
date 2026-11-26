#include "zoid.h"
#include "game_camera.h"
#include "model_archive.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void jobjDispAll(HSD_JObj *joint);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern ModelArchive *dsp1p;
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

static inline s32 zdOptionReady(ZoidState *zoid)
{
    s32 ready = 1;
    if (zoid->option_energy_max != zoid->option_energy && (s8)zoid->option_use_state == 0) {
        ready = 0;
    }
    return ready;
}

void s1pOption(CameraState *camera, ZoidState *zoid, HSD_JObj *parent)
{
    HSD_JObj *gauge;
    HSD_JObj *child;
    HSD_JObj *icon;
    HSD_JObj *bar;
    HSD_JObj *fill;
    s32 ready;
    f32 ratio;

    if (parent != 0 && zoid != 0 && zoid->joint != 0 && zoid->option_type != 0 && zoid->option_energy_max != 0) {
        child = GetChild(parent, 0, 4, -1, -1, -1);
        if (child != 0) {
            gauge = dsp1p->models[5];
            icon = dsp1p->models[7];
            if (sCamNN == 2 && sCamNS == 1 && camera->half == 0) {
                gauge = dsp1p->models[6];
            }
            if (gauge != 0) {
                jobjCopyPos(child, gauge);
                jobjCopyPos(child, icon);
                ready = zdOptionReady(zoid);
                bar = GetChild(gauge, 0, ready ? 0 : 1, -1, -1, -1);
                ratio = (f32)zoid->option_energy / (f32)zoid->option_energy_max;
                fill = GetChild(bar, 0, 0, -1, -1, -1);
                HSD_JObjSetScaleX(fill, ratio);
                jobjDispAll(bar);
                icon = GetChild(icon, 0, zoid->option_type - 1, -1, -1, -1);
                HiddenParts(icon, !ready);
                HiddenParts(GetChild(icon, 0, 0, -1, -1, -1), ready);
                jobjDispAll(icon);
            }
        }
    }
}
