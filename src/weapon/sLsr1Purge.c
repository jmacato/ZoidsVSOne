#include "weapon.h"

extern void HSD_JObjRemoveAnimAll(HSD_JObj *joint);
extern void psKillJObjAllGenerator(HSD_JObj *joint);
extern void HSD_JObjUnref(HSD_JObj *joint);

void sLsr1Purge(Lsr1 *laser)
{
    if (laser != 0 && laser->joint != 0) {
        HSD_JObjRemoveAnimAll(laser->joint);
        psKillJObjAllGenerator(laser->joint);
        HSD_JObjUnref(laser->joint);
        laser->joint = 0;
    }
}
