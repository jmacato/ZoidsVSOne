#pragma readonly_strings on
#include "model_archive.h"
#include "video.h"
#include "fog.h"
#include "ground_object.h"

extern ModelArchive Ground;
extern ModelArchive *Sky;
extern struct HSD_Fog *fogG;
extern s32 objNow, objSize;
extern void GroundObjPurge(void);
extern void PurgeArc(ModelArchive *);
extern void sColEpilogue(void);
extern void sMakeMatrix(HSD_JObj *);
extern void OSReport(const char *, ...);
extern GXColor SkyAmbient;
extern s32 sprintf(char *buffer, const char *format, ...);
extern void LoadArcU(ModelArchive *archive, char *name, s32 usb);
extern ModelArchive *LoadArc2USB(char *name);
extern void setModelShadow2(HSD_JObj *joint);
extern void getSkyAmbient(void);
extern void jobjAmbient(HSD_JObj *joint, GXColor *color);
extern void GroundObjLoad(s32 stage, s32 usb);
extern s32 clipDat[];
extern s32 nowStage;
extern s32 sDispClipOnOff;
extern void PurgeStageData(void);
extern void LoadStageData2(s32 stage);
extern void LoadStageDataUSB2(s32 stage);
extern void sColPrologue(char *name, s32 usb);

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern s32 objHP[];
extern s32 objShadowRecv[];
extern void setModelShadow(HSD_JObj *joint);
extern s32 fileLen(char *name);
extern HSD_JObj *CopyJoint2(ModelArchive *archive, s32 model);
extern void sGlobal2Local(HSD_JObj *joint);
extern void PSMTXInverse(f32 src[3][4], f32 dst[3][4]);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static ModelArchive *GroundObj[6];
static GroundObject obj[50];

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

static inline f32 HSD_JObjGetScaleY(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 911, "jobj");
    return jobj->scale.y;
}


static void GroundObjLoadSub2(HSD_JObj *joint, s32 stage, s32 usb)
{
    char name[264];
    GXColor color;
    s32 j;
    s32 i;
    s32 type;
    HSD_JObj *copy;

    if (joint == NULL)
        return;
    if (objNow >= 50)
        return;
    if (stage < 0)
        return;
    type = (s32)HSD_JObjGetScaleY(joint) - 1;
    if (type == 0)
        return;
    if (type >= 6)
        return;
    if (GroundObj[type] == NULL) {
        sprintf(name, "stage/map_obj/map_obj%02d.dat", type);
        if (usb != 0)
            GroundObj[type] = LoadArc2USB(name);
        else
            GroundObj[type] = LoadArc2(name);
        if (GroundObj[type] != NULL) {
            if (objShadowRecv[type] != 0)
                setModelShadow(GroundObj[type]->models[0]);
            color = SkyAmbient;
            jobjAmbient(GroundObj[type]->models[0], &color);
            objSize += fileLen(name);
        }
    }
    if (GroundObj[type] == NULL)
        return;
    obj[objNow].source = joint;
    sMakeMatrix(joint);
    for (i = 0; i < 3; i++)
        obj[objNow].position[i] = joint->matrix[i][3];
    obj[objNow].archive_slot = type;
    copy = CopyJoint2(GroundObj[type], 0);
    obj[objNow].joint = copy;
    obj[objNow].animation = GROUND_OBJECT_ANIM_INTACT;
    obj[objNow].health = objHP[type];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            copy->matrix[i][j] = joint->matrix[i][j];
        obj[objNow].position[i] = joint->matrix[i][j];
    }
    sGlobal2Local(copy);
    HSD_JObjSetScaleX(copy, 1.0f);
    HSD_JObjSetScaleY(copy, 1.0f);
    HSD_JObjSetScaleZ(copy, 1.0f);
    sMakeMatrix(copy);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            obj[objNow].matrix[i][j] = copy->matrix[i][j];
    }
    PSMTXInverse(obj[objNow].matrix, obj[objNow].inverse);
    grdObjSetAnim(&obj[objNow], GROUND_OBJECT_ANIM_INTACT);
    objNow++;
}

#pragma dont_inline on
void GroundObjLoadSub(HSD_JObj *joint, s32 stage, s32 usb)
{
    if (joint != 0) {
        for (joint = joint != 0 ? joint->child : 0; joint != 0;
             joint = joint != 0 ? joint->next : 0)
            GroundObjLoadSub2(joint, stage, usb);
    }
}

void GroundObjLoad(s32 stage, s32 usb)
{
    HSD_JObj *joint = Ground.models[0];
    if (joint != 0) {
        sMakeMatrix(joint);
        joint = joint != 0 ? joint->child : 0;
        objSize = 0;
        for (; joint != 0; joint = joint != 0 ? joint->next : 0)
            GroundObjLoadSub(joint, stage, usb);
        sMakeMatrix(Ground.models[0]);
        OSReport("ground stage=%d , obj=%d   objSize=%d  \n", stage, objNow, objSize);
    }
}

s32 LoadStageData2__(s32 stage, s32 usb)
{
    char sky[36];
    char ground[256];
    s32 frame_padding;
    GXColor ambient;

    sprintf(ground, "stage/st%02d.dat", stage);
    LoadArcU(&Ground, ground, usb);
    setModelShadow2(Ground.models[0]);
    sprintf(sky, "stage/skymap%02d.dat", stage);
    if (usb != 0)
        Sky = LoadArc2USB(sky);
    else
        Sky = LoadArc2(sky);
    fogG = Sky->fog;
    if (fogG != 0)
        HSD_VIData.current.vi.clear_clr = fogG->color;
    getSkyAmbient();
    ambient = SkyAmbient;
    jobjAmbient(Ground.models[0], &ambient);
    GroundObjLoad(stage, usb);
    return 1;
}

void PurgeStageData(void)
{
    OSReport("stage ");
    GroundObjPurge();
    OSReport("gObj.. ");
    PurgeArc(&Ground);
    OSReport("grdPurge.. ");
    PurgeArc2(Sky);
    Sky = 0;
    OSReport("sky.. ");
    if (fogG != 0)
        fogG = 0;
    sColEpilogue();
}
