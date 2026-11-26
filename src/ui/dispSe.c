#include "model_archive.h"
#include "game_text.h"

extern s32 crN;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void jobjDispAll(HSD_JObj *joint);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 VolSe;

void dispSe(ModelArchive *archive)
{
    s32 i;

    if (crN != 2)
        return;
    jobjDispAll(archive->models[19]);
    for (i = 0; i < 10; i++)
        HiddenParts(GetChild(archive->models[20], 0, i, 0, -1, -1), i >= VolSe);
    jobjDispAll(archive->models[20]);
}
