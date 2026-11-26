#include "missile.h"

extern void sMove(Missile *missile);
extern void sHitOn(Missile *missile);
extern void sAtack(Missile *missile);

static inline void sMissilePurgeOld(void)
{
    s32 i;
    for (i = 0; i < 200; i++) {
        if ((missileStart[i].flags & MISSILE_FLAG_ACTIVE) && missileStart[i].purge_timer != 0) {
            missileStart[i].purge_timer++;
            if (missileStart[i].purge_timer > 5)
                sMissilePurge(&missileStart[i]);
        }
    }
}

void sMissileMove(void)
{
    s32 i;
    Missile *missile = missileStart;

    for (i = 0; i < 200; i++, missile++) {
        if (missile->flags & MISSILE_FLAG_ACTIVE) {
            sMove(missile);
            sHitOn(missile);
            sAtack(missile);
        }
    }
    sMissilePurgeOld();
}
