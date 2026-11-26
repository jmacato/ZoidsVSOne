#include "model_archive.h"

extern ModelArchive *dsp1p;
extern s32 gameTime;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern s32 jobjAnim(HSD_JObj *joint);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

void s1pTimer(HSD_JObj *joint)
{
    s32 digits[4];
    HSD_JObj *source;
    HSD_JObj *timer;
    HSD_JObj *position;
    HSD_JObj *number;
    s32 seconds;
    s32 i;

    if (gameTime <= 0)
        return;
    if (dsp1p == 0)
        return;
    if (joint == 0)
        return;
    source = GetChild(joint, 0, 8, -1, -1, -1);
    if (source == 0)
        return;
    timer = dsp1p->models[13];
    if (timer == 0)
        return;
    jobjCopyPos(source, timer);
    seconds = gameTime / 60;
    digits[3] = seconds % 10;
    seconds /= 10;
    digits[2] = seconds % 6;
    seconds /= 6;
    digits[1] = seconds % 10;
    seconds /= 10;
    digits[0] = seconds % 6;
    if (gameTime == 1800)
        SetAnimArc2(dsp1p, 13, 1);
    jobjAnim(timer);
    HSD_JObjDisp(GetChild(timer, 0, -1, -1, -1, -1), 0, 7, 0);
    for (i = 0; i < 4; i++) {
        position = GetChild(timer, 0, 13 - i, -1, -1, -1);
        number = GetChild(timer, 0, digits[i], -1, -1, -1);
        jobjCopyPos(position, number);
        HSD_JObjDisp(number, 0, 7, 0);
    }
}
