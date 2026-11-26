#include "weapon.h"

extern void HSD_JObjDispAll(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);

void sLsrDisp(void)
{
    s32 i;
    for (i = 0; i < 400; i++) {
        if (sLsr1[i].joint != 0)
            HSD_JObjDispAll(sLsr1[i].joint, 0, 7, 0);
    }
}
