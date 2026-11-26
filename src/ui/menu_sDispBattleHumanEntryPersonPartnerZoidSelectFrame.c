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

void menu_sDispBattleHumanEntryPersonPartnerZoidSelectFrame(void)
{
    HSD_JObj *source;
    HSD_JObj *target;
    s16 selected;

    if (menumode == 2 && menufarmcl[menumode] == 2)
        return;
    if (menumode != 2)
        return;
    selected = menufarmcl[2];
    if (menucuranm == 1) {
        SetAnimArc2(menu1p, 5, 0);
        menucuranm = 2;
    }
    if (menucuranm == 2) {
        if (jobjAnim(menu1p->models[5]) != 0)
            menucuranm = 3;
    } else if (menucuranm == 3) {
        SetAnimArc2(menu1p, 5, 0);
        jobjAnim(menuModel(5));
        menucuranm = 2;
    }
    source = GetChild(menuModel(4), 0, selected, 1, -1, -1);
    target = GetChild(menuModel(5), 0, 0, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDisp(target, 0, 7, 0);
}
