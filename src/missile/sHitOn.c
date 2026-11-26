#include "missile.h"

extern s32 sAObjAnimeAll(HSD_JObj *joint);
extern void TEA_VidOff(u32 voice);

void sHitOn(Missile *missile)
{
    if (missile != 0) {
        missile->update_count++;
        if (missile->purge_timer == 0 && missile->hit != 0) {
            if (sAObjAnimeAll(missile->joint) != 0)
                missile->purge_timer = 1;
            if (missile->se_playing != 0) {
                missile->se_playing = 0;
                TEA_VidOff(missile->se_voice);
            }
            msFlyTrace(missile);
        }
    }
}
