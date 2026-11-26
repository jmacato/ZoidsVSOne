#include "zoid.h"
#include "model_archive.h"
#include "matrix.h"
#include "game_camera.h"
#include "game_mode.h"

extern ModelArchive *dspRader, *dsp1p, *dspPartner, *dspPoint, *dspPos00;
extern HSD_JObj *dspJobjEx3[2];
extern s32 dspAnmEx3[2];
extern s32 dspAnmEx3n[2];
extern s32 dspPartnerMsg, dspPartnerMsgA, dspPartnerMsgB;
extern s32 nowStage;
extern s32 sCamNN, sCamNS;
extern s32 menuRet;
extern HSD_JObj *jobjFilter[3];
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *CopyJoint2(ModelArchive *archive, s32 model);
extern void sDispLoadPartsWarn(void);
extern void sDispLoadPartsPause(void);
extern ModelArchive *dspMessage;
extern s32 gameEndF;
extern void HSD_CObjGetScissor(struct HSD_CObj *cobj, u16 *scissor);
extern void HSD_CObjSetScissor(struct HSD_CObj *cobj, u16 *scissor);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void sDispPartner(CameraState *camera);
extern void sDispFilter(CameraState *camera, struct ZoidState *zoid);
extern void sDispFilterG(void), sDispFilterB(void);
extern void sDisp1pA(CameraState *camera);
extern void sDispPause(CameraState *camera);
extern void sDispLoadPartsMessage(void), sDispLoadPartsContinue(void), sDispLoadPartsBP(void);
extern void sDispMessage(CameraState *camera);
extern void sDispBP(CameraState *camera);
extern void sDispNext(CameraState *camera);
extern ModelArchive *dspFilter;
extern void LoadArcAnimModel2(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 selected);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void jobjUnrefAll(HSD_JObj *joint);
extern void sDispPurgePartsWarn(void), sDispPurgePartsPause(void), sDispPurgePartsBP(void);
extern void sDispPurgePartsContinue(void), sDispPurgePartsMessage(void);

static Mtx dspMtx;
static s32 anmFilter[3];
HSD_JObj *jobjFilter[3];

static const char sMessageArchivePath[21] = "disp/div/message.dat";
static const char sContinueArchivePath[22] = "disp/div/continue.dat";
static const char sWarningArchivePath[21] = "disp/div/warning.dat";
static const char sBpArchivePath[16] = "disp/div/bp.dat";
static const char sPauseArchivePath[19] = "disp/div/pause.dat";

#pragma readonly_strings on
void sDispLoadParts(s32 mode)
{
    char rader[100];
    char partner[256];

    dspRader = 0;
    dsp1p = 0;
    dspPos00 = 0;
    dspJobjEx3[0] = 0;
    dspJobjEx3[1] = 0;
    anmFilter[0] = -1;
    anmFilter[1] = -1;
    anmFilter[2] = -1;
    dspPartnerMsg = -1;
    dspPartnerMsgB = -1;
    dspPartnerMsgA = 0;
    if (mode == 1 && Zoid[2].joint != 0 && Zoid[0].slot == Zoid[2].slot) {
        sprintf(partner, "chara/bp/bp%02d.dat", Zoid[2].person);
        dspPartner = LoadArc2(partner);
        SetAnimArc2(dspPartner, 0, 0);
    }
    dspPos00 = LoadArc2("disp/position00.dat");
    dspPoint = LoadArc2("disp/point.dat");
    if (dspPos00 != 0)
        dsp1p = LoadArc2("disp/interface.dat");
    sprintf(rader, "disp/radar%02d.dat", nowStage);
    dspRader = LoadArc2(rader);
    dspJobjEx3[0] = CopyJoint2(dsp1p, 3);
    dspAnmEx3[0] = 3;
    dspAnmEx3n[0] = -1;
    dspAnmEx3n[1] = -1;
    if (sCamNN == 2 && sCamNS == 1)
        dspAnmEx3[1] = 4;
    else
        dspAnmEx3[1] = 3;
    dspJobjEx3[1] = CopyJoint2(dsp1p, dspAnmEx3[1]);
    menuRet = 0;
    PSMTXTrans(dspMtx, 0.0f, 0.0f, 0.0f);
    sDispLoadPartsWarn();
    sDispLoadPartsPause();
}
#pragma readonly_strings off

#pragma auto_inline off
static void sDispPurgePartsGame(void)
{
    if (dspJobjEx3[0] != 0)
        jobjUnrefAll(dspJobjEx3[0]);
    if (dspJobjEx3[1] != 0)
        jobjUnrefAll(dspJobjEx3[1]);
    dspJobjEx3[0] = 0;
    dspJobjEx3[1] = 0;
    if (dspRader != 0)
        PurgeArc2(dspRader);
    dspRader = 0;
    if (dsp1p != 0)
        PurgeArc2(dsp1p);
    dsp1p = 0;
    if (dspPartner != 0)
        PurgeArc2(dspPartner);
    dspPartner = 0;
    if (dspPoint != 0)
        PurgeArc2(dspPoint);
    dspPoint = 0;
    sDispPurgePartsWarn();
    sDispPurgePartsPause();
}

void sDispPurgeParts(void)
{
    sDispPurgePartsGame();
    if (dspPos00 != 0)
        PurgeArc2(dspPos00);
    dspPos00 = 0;
    sDispPurgePartsBP();
    sDispPurgePartsContinue();
    sDispPurgePartsPause();
    sDispPurgePartsMessage();
    sDispPurgePartsPause();
}

void sDispGameFilter(s32 index, s32 mode)
{
    s32 next;

    if (index < 0)
        return;
    if (index > 2)
        return;
    if (jobjFilter[index] == 0)
        return;
    if (dspFilter == 0)
        return;
    if (anmFilter[index] == -1) {
        if (mode == 0)
            return;
        if (mode == 1)
            next = 0;
        else
            next = 3;
        LoadArcAnimModel2(dspFilter, jobjFilter[index], 0, next);
        anmFilter[index] = next;
        return;
    }
    if (jobjAnim(jobjFilter[index]) != 0) {
        next = anmFilter[index];
        switch (next) {
        case 0:
            next = 1;
            break;
        case 1:
            if (mode == 1)
                break;
            next = 2;
            break;
        case 2:
            next = -1;
            break;
        case 3:
            next = 4;
            break;
        case 4:
            if (mode == 2)
                break;
            next = 5;
            break;
        case 5:
            next = -1;
            break;
        default:
            return;
        }
        if (next != anmFilter[index]) {
            if (next != -1) {
                LoadArcAnimModel2(dspFilter, jobjFilter[index], 0, next);
                jobjAnim(jobjFilter[index]);
            }
            anmFilter[index] = next;
        }
        if (next == -1)
            return;
    }
    jobjDispAll(jobjFilter[index]);
}

void sDisp(CameraState *camera)
{
    u16 scissor[6];
    s32 filtered;

    if (camera == 0)
        return;
    if (camera->cobj == 0)
        return;
    filtered = 0;
    HSD_CObjGetScissor(camera->cobj, scissor);
    if (dsp1p != 0)
        HSD_CObjSetScissor(dsp1p->camera, scissor);
    if (dspMessage != 0)
        HSD_CObjSetScissor(dspMessage->camera, scissor);
    HSD_SetZSortMode(0, 0);
    if (dsp1p != 0 && HSD_CObjSetCurrent(dsp1p->camera) != 0) {
        HSD_LObjSetCurrentAll(camera->lights);
        HSD_LObjSetupInit(dsp1p->camera);
        GXSetCullMode(0);
        sDispPartner(camera);
        sDispFilter(camera, camera->zoid);
        filtered = 1;
        sDispFilterG();
        if (gameEndF < 3)
            sDisp1pA(camera);
        sDispPause(camera);
        HSD_CObjEndCurrent();
    }
    if (gameEndF >= 4)
        sDispPurgePartsGame();
    if (gameEndF >= 4)
        sDispLoadPartsMessage();
    if (gameEndF >= 9)
        sDispLoadPartsContinue();
    if (gameEndF == 11 && GameMode.game_type == GAME_TYPE_BATTLE)
        sDispLoadPartsBP();
    if (dspMessage != 0 && HSD_CObjSetCurrent(dspMessage->camera) != 0) {
        HSD_LObjSetCurrentAll(camera->lights);
        HSD_LObjSetupInit(dspMessage->camera);
        GXSetCullMode(0);
        if (filtered == 0)
            sDispFilterG();
        if (gameEndF >= 4)
            sDispMessage(camera);
        sDispFilterB();
        sDispBP(camera);
        sDispNext(camera);
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_SetZSortMode(1, 1);
}
