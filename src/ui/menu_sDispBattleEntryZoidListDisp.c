#include "model_archive.h"
#include "game_zoid_data.h"
#include "game_text.h"

extern ModelArchive *menu1p;
extern ModelArchive *menu_zoidp[100];
extern s16 menumode;
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

void menu_sDispBattleEntryZoidListDisp(s16 zoid, s16 slot)
{
    char text[80];
    HSD_JObj *source;
    HSD_JObj *target;

    if (menumode != 7 && menumode != 8)
        return;
    if (zoid == -1)
        return;
    source = GetChild(menu1p->models[6], 0, 2, 4, slot, -1);
    target = GetChild(menu1p->models[6], 0, 2, 3, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDispAll(target, 0, 7, 0);
    source = GetChild(menu1p->models[6], 0, 2, 4, slot, -1);
    if (menu_zoidp[zoid] == 0)
        return;
    target = GetChild(menu_zoidp[zoid]->models[0], 0, 1, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDispAll(target, 0, 7, 0);
    sprintf(text, " %s", Tea_zoiddat[zoid].name);
    putAscJobj(source, 0, text);
}
