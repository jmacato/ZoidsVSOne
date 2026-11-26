#include "zoid.h"
#include "game_camera.h"
#include "model_archive.h"
#include "ground_collision.h"

#define NULL 0

extern ModelArchive *dspWarn;
extern s32 pause;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HiddenPartsAll(HSD_JObj *joint, s32 hidden);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 HSD_JObjGetScaleY(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 911, "jobj");
    return jobj->scale.y;
}

static inline void sDispAreaWarn(ZoidState *zoid, HSD_JObj *source)
{
    HSD_JObj *area;

    area = dspWarn->models[6];
    jobjCopyPos(source, area);
    sMakeMatrix(area);
    HiddenPartsAll(GetChild(area, 0, 1, -1, -1, -1), 1);
    HiddenPartsAll(GetChild(area, 0, 2, -1, -1, -1), 1);
    HiddenPartsAll(GetChild(area, 0, 0, -1, -1, -1), 0);
    if (zoid->ground_polygon == GROUND_POLYGON_NONE)
        return;
    if ((grdcMat[grdcPolygon[zoid->ground_polygon].material].bits[0] & 6) == 0)
        return;
    if (pause == 0 && jobjAnim(area) != 0)
        SetAnimArc2(dspWarn, 6, 1);
    sMakeMatrix(area);
    if (HSD_JObjGetScaleY(area) != 0.0f)
        jobjDispAll(area);
}

void sDispArea(CameraState *camera, HSD_JObj *joint)
{
    Vec3 pos;
    ZoidState *zoid;
    HSD_JObj *source;

    if (camera == NULL)
        return;
    zoid = camera->zoid;
    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    source = GetChild(joint, 0, 11, -1, -1, -1);
    if (dspWarn == NULL)
        return;
    sDispAreaWarn(zoid, source);
}
