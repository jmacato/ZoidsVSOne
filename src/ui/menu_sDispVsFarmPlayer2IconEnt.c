#include "model_archive.h"

extern ModelArchive *menu1p;
extern s16 menufarmcl[];
extern s16 flag_VsFarmPlayer2Icon;
extern u8 menuZoidBattleModeSingleTeam;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

static inline HSD_JObj *menuModel(s32 i)
{
    HSD_JObj *j = menu1p->models[i];
    return j;
}

static inline HSD_JObj *menuChild(s32 m, s32 a, s32 b)
{
    HSD_JObj *ret = GetChild(menuModel(m), 0, a, b, -1, -1);
    return ret;
}

void menu_sDispVsFarmPlayer2IconEnt(void)
{
    HSD_JObj *source;
    HSD_JObj *target;

    flag_VsFarmPlayer2Icon = menufarmcl[1];
    if (flag_VsFarmPlayer2Icon == -1)
        return;
    if (menuZoidBattleModeSingleTeam != 1)
        return;
    if (flag_VsFarmPlayer2Icon == 3)
        source = GetChild(menuModel(3), 0, 3, 2, -1, -1);
    else
        return;
    target = menuChild(5, 0, -1);
    jobjCopyPos(source, target);
    HSD_JObjDispAll(target, 0, 7, 0);
}
