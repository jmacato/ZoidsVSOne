#pragma readonly_strings on
#include "types.h"

extern s32 clipDat[];
extern s32 nowStage;
extern s32 sDispClipOnOff;
extern void OSReport(const char *format, ...);
extern s32 sprintf(char *buffer, const char *format, ...);
extern void PurgeStageData(s32 stage);
extern void LoadStageData2(s32 stage);
extern void LoadStageDataUSB2(s32 stage);
extern void sColPrologue(char *name, s32 mode);

/* unreferenced, keeps the unit's .rodata layout */
#pragma force_active on
static const char sMapObjPathFormat[30] = "stage/map_obj/map_obj%02d.dat";
static const char sGroundObjReportFormat[41] = "ground stage=%d , obj=%d   objSize=%d  \n";
static const char sStagePathFormat[17] = "stage/st%02d.dat";
static const char sSkymapPathFormat[21] = "stage/skymap%02d.dat";
static const char sGrdPurgeReport[12] = "grdPurge.. ";
#pragma force_active off

void ssLoadStageNow(s32 stage, s32 mode)
{
    char dat_name[40];
    char collision_name[40];
    s32 clip;

    if (stage < 0)
        return;
    clip = clipDat[stage];
    if (clip == 9)
        stage = 3;
    OSReport("load stage %d    clip=%d\n", stage, clip);
    sDispClipOnOff = clipDat[stage];
    if (nowStage != -1)
        PurgeStageData(nowStage);
    sprintf(dat_name, "st%02d.dat", stage);
    sprintf(collision_name, "st%02d.xb", stage);
    if (mode != 0)
        LoadStageDataUSB2(stage);
    else
        LoadStageData2(stage);
    sColPrologue(collision_name, mode);
    nowStage = stage;
}
