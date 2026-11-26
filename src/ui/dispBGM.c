#pragma readonly_strings on
#include "model_archive.h"
#include "game_text.h"

extern s32 crN;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void jobjDispAll(HSD_JObj *joint);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 VolBgm;
extern s32 TestBgm;

void dispBGM(ModelArchive *archive)
{
    char text[12];
    s32 i;

    if (crN != 0)
        return;
    jobjDispAll(archive->models[6]);
    jobjDispAll(archive->models[7]);
    for (i = 0; i < 10; i++)
        HiddenParts(GetChild(archive->models[10], 0, i, 0, -1, -1), i >= VolBgm);
    jobjDispAll(archive->models[10]);
    jobjDispAll(archive->models[11]);
    sprintf(text, "%02d", TestBgm);
    putAscJobj(GetChild(archive->models[11], 0, 1, -1, -1, -1), 3, text);
}
