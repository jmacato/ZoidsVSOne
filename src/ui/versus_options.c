#include "model_archive.h"

extern s32 crN, VsTime;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third,
                         s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void jobjDispAll(HSD_JObj *joint);

void dispVsTime(ModelArchive *archive)
{
    s32 i;
    if (crN == 4) {
        for (i = 0; i < 5; i++)
            HiddenParts(GetChild(archive->models[21], 0, i, 0, -1, -1), i != VsTime);
        jobjDispAll(archive->models[21]);
    }
}
