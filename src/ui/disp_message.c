#include "model_archive.h"
#include "game_mode.h"
#include "game_camera.h"
#include "zoid.h"

extern ModelArchive *dspContinue;
extern s32 gameEndF;
extern s32 gameContinueTm;
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);

extern ModelArchive *dspMessage;
extern ModelArchive *dspPos00;
extern s32 winF;
extern void sDispLoadPartsMessage(void);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern s32 getEndF(HSD_JObj *joint);
extern void jobjDisp(HSD_JObj *joint);
extern s32 HSD_Randi(s32 max);

void sDispMessageMe(CameraState *camera)
{
    static s8 bJa;
    s32 result[4] = {2, 0, 2, 1};
    s32 result4[4] = {8, 7, 8, 8};
    s32 unused;
    HSD_JObj *joint;
    HSD_JObj *child;
    s32 index;

    if (gameEndF < 4)
        return;
    if (gameEndF == 4)
        sDispLoadPartsMessage();
    if (dspMessage == 0)
        return;
    joint = dspMessage->models[5];
    if (joint == 0)
        return;
    if (gameEndF > 11)
        return;
    child = 0;
    if (dspPos00 != 0 && sCamNN == 2)
        child = GetChild(dspPos00->models[sCamNS + 1], 0, camera->half, 10, -1, -1);
    if (child != 0)
        jobjCopyPos(child, joint);
    if (camera == sCamera)
        jobjAnim(joint);
    if (gameEndF == 4) {
        bJa = 0;
        return;
    }
    if (winF == 0)
        return;
    switch (bJa) {
    case 0:
        Zoid[0].rumble_timer = 0;
        Zoid[1].rumble_timer = 0;
        if (GameMode.game_type == GAME_TYPE_BATTLE && camera->zoid == 0 && winF == 1)
            HSD_Randi(4);
        SetAnimArc2(dspMessage, 5, 0);
        bJa = 1;
        return;
    case 1:
        if (getEndF(joint) != 0) {
            SetAnimArc2(dspMessage, 5, 1);
            bJa = 2;
        }
        break;
    case 2:
        if (gameEndF == 6)
            bJa = 3;
        else
            getEndF(joint);
        break;
    case 3:
        SetAnimArc2(dspMessage, 5, 2);
        bJa = 4;
        break;
    case 4:
        if (getEndF(joint) != 0) {
            SetAnimArc2(dspMessage, 5, 3);
            bJa = 5;
            return;
        }
        break;
    case 5:
        return;
    }
    index = result[winF];
    if (sCamNN == 2) {
        if (index == 0) {
            if (camera->half == 0)
                index = 3;
            else
                index = 4;
        }
        if (index == 1) {
            if (camera->half == 0)
                index = 4;
            else
                index = 3;
        }
    }
    if (GameMode.game_type == GAME_TYPE_MISSION)
        index = result4[winF];
    child = GetChild(joint, 0, 9, -1, -1, -1);
    HiddenParts(child, 0);
    jobjDisp(child);
    child = GetChild(joint, 0, index, -1, -1, -1);
    HiddenParts(child, 0);
    jobjDisp(child);
}

void sDispContinue(void *enable)
{
    static s32 cont;
    s32 i;
    s32 time;
    HSD_JObj *base;
    HSD_JObj *yes;
    HSD_JObj *no;
    HSD_JObj *count;

    if (gameEndF < 9) {
        cont = 0;
        return;
    }
    if (dspContinue == 0)
        return;
    if (enable == 0)
        return;
    if (gameEndF >= 11)
        return;
    if (GameMode.game_type != GAME_TYPE_BATTLE)
        return;
    base = dspContinue->models[0];
    yes = dspContinue->models[1];
    no = dspContinue->models[2];
    count = dspContinue->models[3];
    if (base == 0)
        return;
    if (yes == 0)
        return;
    if (no == 0)
        return;
    if (count == 0)
        return;
    if (jobjAnim(yes) != 0)
        SetAnimArc2(dspContinue, 1, GameMode.win == 3 ? 2 : 1);
    if (jobjAnim(no) != 0)
        SetAnimArc2(dspContinue, 2, GameMode.win == 0 ? 2 : 1);
    jobjAnim(count);
    switch (cont) {
    case 0:
        SetAnimArc2(dspContinue, 0, 1);
        SetAnimArc2(dspContinue, 3, 1);
        cont = 1;
        break;
    case 1:
        jobjAnim(base);
        if (gameEndF == 10) {
            SetAnimArc2(dspContinue, 0, 2);
            SetAnimArc2(dspContinue, 3, 2);
            cont = 2;
        }
        break;
    case 2:
        if (jobjAnim(base) != 0) {
            gameEndF = 12;
            return;
        }
        break;
    }
    for (i = 0; i < 4; i++)
        HiddenParts(GetChild(base, 0, i, -1, -1, -1), i != 0);
    jobjDispAll(base);
    if (gameContinueTm > 0) {
        jobjDispAll(yes);
        jobjDispAll(no);
    } else if (GameMode.win == 3) {
        jobjDispAll(yes);
    } else {
        jobjDispAll(no);
    }
    time = gameContinueTm / 60 / 2;
    if (time >= 0 && time < 10) {
        for (i = 0; i < 10; i++)
            HiddenParts(GetChild(count, 0, i, -1, -1, -1), time != i);
    }
    if (GameMode.win == 3 && gameEndF == 10)
        return;
    jobjDispAll(count);
}
