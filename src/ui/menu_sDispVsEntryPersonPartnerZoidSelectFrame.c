#include "model_archive.h"

extern ModelArchive *menu1p;
extern s16 menufarmcl[];
extern s8 vsman;
extern s8 menuvsmode[4];
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

static inline HSD_JObj *menuModel(s32 i)
{
    HSD_JObj *j = menu1p->models[i];
    return j;
}

void menu_sDispVsEntryPersonPartnerZoidSelectFrame(void)
{
    HSD_JObj *source;
    HSD_JObj *target;
    s16 column;
    s16 selected;
    s32 mode = menuvsmode[vsman];

    if (mode != vsman)
        return;
    selected = menufarmcl[mode];
    if (selected == 0)
        column = 1;
    else if (selected == 2)
        column = 2;
    else
        return;
    source = GetChild(menuModel(6), 0, vsman, column, -1, -1);
    target = GetChild(menuModel(7), 0, 0, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDisp(target, 0, 7, 0);
}
