#include "model_archive.h"

extern s32 crN;
extern s32 rumble;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void jobjDispAll(HSD_JObj *joint);

void dispRumble(ModelArchive *archive)
{
    s32 i;

    if (crN != 3)
        return;
    for (i = 0; i < 2; i++)
        HiddenParts(GetChild(archive->models[14], 0, i, 0, -1, -1), i == rumble);
    jobjDispAll(archive->models[14]);
}
