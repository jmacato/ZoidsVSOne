#include "model_archive.h"
#include "game_person_data.h"
#include "game_zoid_data.h"
#include "game_text.h"

extern ModelArchive *menu1p;
extern ModelArchive *menu_personp[58];
extern ModelArchive *menu_zoidp[100];
extern s8 vsman;
extern s32 flag_menuvsentzoid[2];
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

void menu_sDispVsEntryZoidListDisp(s16 index, s16 slot)
{
    char text[100];
    HSD_JObj *source;
    HSD_JObj *target;

    if (flag_menuvsentzoid[vsman] == 0)
        return;
    source = GetChild(menu1p->models[9], 0, vsman, 3, slot, -1);
    target = GetChild(menu1p->models[8], 0, 0, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDispAll(target, 0, 7, 0);
    source = GetChild(menu1p->models[8], 0, 0, -1, -1, -1);
    target = GetChild(menu_zoidp[(s16)index]->models[0], 0, 1, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDispAll(target, 0, 7, 0);
    sprintf(text, " %s", Tea_zoiddat[(s16)index].name);
    putAscJobj(source, 0, text);
}
