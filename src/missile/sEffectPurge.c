#include "missile.h"

extern void TEA_VidOff(u32 voice);
extern void jobjUnrefAll(HSD_JObj *joint);

void sEffectPurge(Effect *effect)
{
    if (effect != 0 && effect->root != 0) {
        if (effect->se_playing != 0) {
            effect->se_playing = 0;
            TEA_VidOff(effect->se_voice);
        }
        jobjUnrefAll(effect->root);
        effect->root = 0;
    }
}
