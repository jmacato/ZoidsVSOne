#include "model_archive.h"
#include "game_save.h"

extern ModelArchive *menu1p;
extern s32 jobjAnim(HSD_JObj *joint);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third,
                         s32 fourth, s32 fifth);
extern void HSD_JObjDispAll(HSD_JObj *joint, void *matrix, u32 flags, u32 mode);

void menu_sDispBattleMsgArea(void)
{
    HSD_JObj *joint;
    s32 country;

    if (jobjAnim(menu1p->models[4]) != 0) {
        SetAnimArc2(menu1p, 4, 1);
        jobjAnim(menu1p->models[4]);
    }
    country = IveSave[0].country;
    joint = GetChild(menu1p->models[4], 0, country, -1, -1, -1);
    HSD_JObjDispAll(joint, 0, 7, 0);
}

void menu_sDispBattleFarmMsgWindowHelp(void)
{
    HSD_JObj *joint;
    s32 country;

    if (jobjAnim(menu1p->models[4]) != 0) {
        SetAnimArc2(menu1p, 4, 1);
        jobjAnim(menu1p->models[4]);
    }
    country = IveSave[0].country;
    joint = GetChild(menu1p->models[4], 0, country, -1, -1, -1);
    HSD_JObjDispAll(joint, 0, 7, 0);
}
