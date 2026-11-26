#include "model_archive.h"

extern ModelArchive *menu1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
void menu_sDispBattleSetLButtonEtc(void)
{
    s32 model = 9;
    s32 i;
    s32 n = 4;

    for (i = 0; i < n; i++)
        HSD_JObjDispAll(GetChild(menu1p->models[model], 0, 6, i, -1, -1), 0, 7, 0);
}
