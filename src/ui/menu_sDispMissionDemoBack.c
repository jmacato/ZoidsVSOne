#include "model_archive.h"

extern s16 menudemobg;
extern ModelArchive *menudemo[4];
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjDispAll(HSD_JObj *joint);

void menu_sDispMissionDemoBack(void)
{
    if (menudemobg != -1)
        jobjDispAll(GetChild(menudemo[3]->models[0], 0, menudemobg, -1, -1, -1));
}
