#pragma readonly_strings on
#include "model_archive.h"
#include "game_text.h"

extern s32 crN;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void jobjDispAll(HSD_JObj *joint);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 VolVoice;
extern s32 TestVoice;

void dispVoice(ModelArchive *archive)
{
    char text[12];
    s32 i;

    if (crN != 1)
        return;
    jobjDispAll(archive->models[8]);
    jobjDispAll(archive->models[9]);
    for (i = 0; i < 10; i++)
        HiddenParts(GetChild(archive->models[12], 0, i, 0, -1, -1), i >= VolVoice);
    jobjDispAll(archive->models[12]);
    jobjDispAll(archive->models[13]);
    sprintf(text, "%03d", TestVoice);
    putAscJobj(GetChild(archive->models[13], 0, 1, -1, -1, -1), 3, text);
}
