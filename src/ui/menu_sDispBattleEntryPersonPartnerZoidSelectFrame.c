#include "model_archive.h"

extern ModelArchive *menu1p;
extern s16 menumode;
extern s16 menufarmcl[];
extern s8 menucuranm;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

static inline HSD_JObj *menuModel(s32 i)
{
    HSD_JObj *j = menu1p->models[i];
    return j;
}

void menu_sDispBattleEntryPersonPartnerZoidSelectFrame(void)
{
    s16 row;
    s16 column;
    HSD_JObj *source;
    HSD_JObj *target;

    row = 0;
    column = 1;
    if (menumode == 2)
        return;
    if (menumode >= 5)
        return;
    if (menumode == 3)
        row = 0;
    if (menumode == 4)
        row = 1;
    if (menufarmcl[menumode] == 0)
        column = 1;
    if (menufarmcl[menumode] == 1)
        column = 2;
    if (menucuranm == 1) {
        SetAnimArc2(menu1p, 7, 0);
        menucuranm = 2;
    }
    if (menucuranm == 2) {
        if (jobjAnim(menu1p->models[7]) != 0)
            menucuranm = 3;
    } else if (menucuranm == 3) {
        SetAnimArc2(menu1p, 7, 0);
        jobjAnim(menuModel(7));
        menucuranm = 2;
    }
    source = GetChild(menuModel(6), 0, row, column, -1, -1);
    target = GetChild(menuModel(7), 0, 0, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDisp(target, 0, 7, 0);
}
