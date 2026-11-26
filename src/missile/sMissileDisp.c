#include "missile.h"
#include "jobj.h"

extern s32 nowMX;
extern s32 misMAX;

void sMissileDisp(void)
{
    Missile *missile;
    s32 i;

    nowMX = 0;
    missile = missileStart;
    for (i = 0; i < 200; i++, missile++) {
        if ((missile->flags & MISSILE_FLAG_ACTIVE) && missile->purge_timer == 0 && missile->joint != 0) {
            nowMX++;
            HSD_JObjDispAll(missile->joint, 0, 7, 0);
        }
    }
    if (nowMX > misMAX) {
        misMAX = nowMX;
    }
}
