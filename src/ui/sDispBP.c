#include "model_archive.h"
#include "game_mode.h"
#include "game_text.h"

extern ModelArchive *dspBP;
extern s32 gameEndF;
extern s32 bpTm;
extern s32 bp[12];
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);

void sDispBP(void *enable)
{
    char text[28];
    HSD_JObj *root;
    HSD_JObj *child;
    s32 total;
    s32 i;

    if (dspBP == 0)
        return;
    root = dspBP->models[10];
    if (enable == 0)
        return;
    if (GameMode.game_type != GAME_TYPE_BATTLE)
        return;
    if (GameMode.win != 2)
        return;
    if (gameEndF != 11)
        return;
    if (bpTm == 0) {
        SetAnimArc2(dspBP, 10, 0);
        bpTm = 1;
    }
    if (jobjAnim(root) != 0)
        SetAnimArc2(dspBP, 10, 1);
    jobjDispAll(root);
    sMakeMatrix(root);
    total = 0;
    for (i = 0; i < 6; i++) {
        s32 index[6] = { 0, 1, 3, 4, 5, 6 };
        child = GetChild(root, 0, index[i], 0, -1, -1);
        if (i == 5)
            sprintf(text, "%06d", bp[i + 6]);
        else
            sprintf(text, "%04d", bp[i + 6]);
        if (i != 5)
            total += bp[i + 6];
        bp[11] = total;
        putAscJobj(child, 3, text);
    }
}
