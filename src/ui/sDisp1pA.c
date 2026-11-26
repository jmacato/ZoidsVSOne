#include "zoid.h"
#include "game_camera.h"
#include "model_archive.h"

extern ModelArchive *dspPos00, *dsp1p;
extern s32 sCamNN, sCamNS;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void s1pZdHP(CameraState *camera, ZoidState *zoid, ModelArchive *archive, HSD_JObj *joint);
extern void s1pEX(CameraState *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pOption(CameraState *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pZdDmg1(ZoidState *zoid, ModelArchive *archive, HSD_JObj *joint);
extern void s1pWeapon(CameraState *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pRader(CameraState *camera, ZoidState *zoid, HSD_JObj *joint);
extern void s1pTimer(HSD_JObj *joint);
extern void s1pTarget(CameraState *camera, ZoidState *zoid);
extern void s1pWpTgt(CameraState *camera, ZoidState *zoid);
extern void sDispArea(CameraState *camera, HSD_JObj *joint);

void sDisp1pA(CameraState *camera)
{
    ZoidState *zoid;
    HSD_JObj *joint;

    zoid = camera->zoid;
    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    if (dspPos00 == 0)
        return;
    if (dsp1p == 0)
        return;
    joint = GetChild(dspPos00->models[1], 0, 0, 8, -1, -1);
    jobjCopyPos(joint, GetChild(dspPos00->models[1], 0, 1, 8, -1, -1));
    joint = GetChild(dspPos00->models[2], 0, 0, 8, -1, -1);
    jobjCopyPos(joint, GetChild(dspPos00->models[2], 0, 1, 8, -1, -1));
    joint = 0;
    if (dspPos00 != 0) {
        if (sCamNN == 1)
            joint = GetChild(dspPos00->models[0], 0, -1, -1, -1, -1);
        else
            joint = GetChild(dspPos00->models[1 + sCamNS], 0, camera->half, -1, -1, -1);
    }
    if (joint == 0)
        return;
    s1pZdHP(camera, zoid, dsp1p, joint);
    s1pEX(camera, zoid, joint);
    s1pOption(camera, zoid, joint);
    s1pZdDmg1(zoid, dsp1p, joint);
    s1pWeapon(camera, zoid, joint);
    s1pRader(camera, zoid, joint);
    s1pTimer(joint);
    s1pTarget(camera, zoid);
    s1pWpTgt(camera, zoid);
    sDispArea(camera, joint);
}
