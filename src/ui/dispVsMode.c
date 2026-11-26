#include "model_archive.h"

extern s32 crN;
extern s32 VsMode;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void jobjDispAll(HSD_JObj *joint);
extern s32 jobjAnim(HSD_JObj *joint);

static inline s32 menuAnim(HSD_JObj *jobj)
{
    s32 done = jobjAnim(jobj);

    return done;
}

void dispVsMode(ModelArchive *archive)
{
    static s32 jk = -1;
    s32 i;

    if (crN != 5) {
        jk = -1;
        return;
    }
    for (i = 0; i < 2; i++)
        HiddenParts(GetChild(archive->models[15], 0, i, 0, -1, -1), i != VsMode);
    jobjDispAll(archive->models[15]);
    if (jk != VsMode) {
        SetAnimArc2(archive, 16, 0);
        jk = VsMode;
    }
    if (menuAnim(archive->models[16]) != 0)
        SetAnimArc2(archive, 16, 1);
    jobjDispAll(GetChild(archive->models[16], 0, VsMode, -1, -1, -1));
}
