#include "missile.h"

void sEffectEpilogue(void)
{
    Effect *effect;
    s32 i;

    PurgeArc2(sEfctLight);
    sEfctLight = 0;
    for (i = 0; i < 100; i++) {
        effect = &sEffect[i];
        sEffectPurge(effect);
        effect->root = 0;
    }
    for (i = 0; i < 110; i++) {
        if (efctFile[i] != 0) {
            PurgeArc2(efctFile[i]);
        }
        efctFile[i] = 0;
    }
}
