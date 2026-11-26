#include "jobj.h"
#include "model_archive.h"
#include "game_camera.h"
#include "video.h"
#include "fog.h"
#include "gx_pixel.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern CameraState *camTmp;
extern ModelArchive *Sky;
extern s32 nowShadow;
extern HSD_Fog *fogG;
extern s32 normLineDEBUG;
extern void sCameraLenZoid(CameraState *camera);
extern void sCameraMatrix(CameraState *camera);
extern void HSD_SetZSortMode(s32 a, s32 b);
extern void HSD_ShadowSetActive(struct HSD_Shadow *shadow, s32 active);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *cobj);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(void *lobj);
extern void HSD_LObjSetupInit(struct HSD_CObj *cobj);
extern void HSD_LObjDeleteCurrentAll(void *lobj);
extern void HSD_FogSet(HSD_Fog *fog);
extern void sMissileLight(void);
extern void grdDisp(void);
extern void sdZoidAll(void);
extern void ZoidTransMode(void);
extern void ZoidAllDisp3(void);
extern void ZoidAllDisp(void);
extern void psDispParticles(s32 mask, s32 pass);
extern void sLsrDisp(void);
extern void grdDispXLU(void);
extern void ZoidAllDispXLU(void);
extern void ZoidAllDBG(void);
extern void sWeaponDispAll(void);
extern void sMissileDisp(void);
extern void sEffectDispAll(void);
extern void sDisp(CameraState *camera);
extern void putErrInt(void);
extern void sPutFontAllN(void);

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

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void draw1(s32 first_camera)
{
    if (camTmp->cobj == NULL)
        return;
    sCameraLenZoid(camTmp);
    HSD_SetZSortMode(1, 1);
    if (nowShadow == 0)
        HSD_ShadowSetActive(camTmp->shadow, 1);
    HSD_StartRender(first_camera ? HSD_RP_OFFSCREEN : HSD_RP_SCREEN);
    if (HSD_CObjSetCurrent(camTmp->cobj)) {
        HSD_LObjSetCurrentAll(camTmp->lights);
        HSD_LObjSetupInit(camTmp->cobj);
        sCameraMatrix(camTmp);
        HSD_FogSet(NULL);
        HSD_JObjSetTranslateX(Sky->models[0], camTmp->relative_origin.x);
        HSD_JObjSetTranslateY(Sky->models[0], camTmp->relative_origin.y);
        HSD_JObjSetTranslateZ(Sky->models[0], camTmp->relative_origin.z);
        HSD_JObjDispAll(Sky->models[0], 0, HSD_TRSP_ALL, 0);
        if (fogG)
            HSD_FogSet(fogG);
        HSD_LObjDeleteCurrentAll(camTmp->lights);
        HSD_LObjSetCurrentAll(camTmp->lights);
        sMissileLight();
        HSD_LObjSetupInit(camTmp->cobj);
        grdDisp();
        sdZoidAll();
        ZoidTransMode();
        if (fogG)
            HSD_FogSet(NULL);
        ZoidAllDisp3();
        if (fogG)
            HSD_FogSet(fogG);
        ZoidAllDisp();
        psDispParticles(0xFFFF, 0);
        if (fogG)
            HSD_FogSet(NULL);
        if (fogG)
            HSD_FogSet(fogG);
        sLsrDisp();
        if (fogG)
            HSD_FogSet(NULL);
        if (fogG)
            HSD_FogSet(fogG);
        if (fogG)
            HSD_FogSet(fogG);
        grdDispXLU();
        ZoidAllDispXLU();
        if (fogG)
            HSD_FogSet(NULL);
        if (fogG)
            HSD_FogSet(NULL);
        if (normLineDEBUG)
            ZoidAllDBG();
        if (fogG)
            HSD_FogSet(fogG);
        HSD_CObjEndCurrent();
        if (fogG)
            HSD_FogSet(NULL);
        HSD_LObjDeleteCurrentAll(camTmp->lights);
        if (fogG)
            HSD_FogSet(NULL);
    }
    HSD_SetZSortMode(0, 0);
    if (fogG)
        HSD_FogSet(NULL);
    if (HSD_CObjSetCurrent(camTmp->cobj)) {
        HSD_LObjSetCurrentAll(camTmp->lights);
        HSD_LObjSetupInit(camTmp->cobj);
        if (fogG)
            HSD_FogSet(fogG);
        sWeaponDispAll();
        if (fogG)
            HSD_FogSet(NULL);
        HSD_CObjEndCurrent();
        HSD_LObjDeleteCurrentAll(camTmp->lights);
    }
    HSD_SetZSortMode(1, 1);
    if (fogG)
        HSD_FogSet(NULL);
    if (HSD_CObjSetCurrent(camTmp->cobj)) {
        HSD_LObjSetCurrentAll(camTmp->lights);
        HSD_LObjSetupInit(camTmp->cobj);
        if (fogG)
            HSD_FogSet(NULL);
        sMissileDisp();
        sEffectDispAll();
        psDispParticles(0xFFFF, 1);
        psDispParticles(0xFFFF, 2);
        HSD_CObjEndCurrent();
    }
    if (fogG)
        HSD_FogSet(NULL);
    HSD_EndRender();
    HSD_StateInvalidate(-1);
    HSD_StartRender(first_camera ? HSD_RP_OFFSCREEN : HSD_RP_SCREEN);
    if (fogG)
        HSD_FogSet(NULL);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    sDisp(camTmp);
    HSD_StateInvalidate(-1);
    if (fogG)
        HSD_FogSet(NULL);
    putErrInt();
    sPutFontAllN();
    HSD_StateInvalidate(-1);
    HSD_EndRender();
    HSD_ShadowSetActive(camTmp->shadow, 0);
}
