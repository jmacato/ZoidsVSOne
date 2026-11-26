#include "missile.h"


void sMissilePurgeAll(void)
{
    s32 i;
    Missile *missile = missileStart;
    for (i = 0; i < 200; i++, missile++) {
        sMissilePurge(missile);
    }
}
