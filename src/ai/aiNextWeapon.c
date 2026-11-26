#include "zoid_ai.h"

s32 aiNextWeapon(s32 index)
{
    s32 tries;
    s32 ready = 1;
    s32 bullet;

    if (aiDat[index].weapon_timer > 0)
        return 0;
    for (tries = 0; tries < 28; tries++) {
        zdAI_WeaponChg(index);
        bullet = zdAI_WeaponBullet(index);
        if (bullet != 0)
            break;
    }
    if (bullet == 0)
        ready = 0;
    aiDat[index].weapon_ready = ready;
    aiDat[index].weapon_timer = 180;
    return ready;
}
