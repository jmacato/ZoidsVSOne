#include "missile.h"
#include "jobj.h"

extern s32 getEndF(HSD_JObj *joint);

void sEffectAnim1(Effect *effect)
{
    if (effect != 0 && effect->root != 0) {
        HSD_JObjAnimAll(effect->root);
        if (getEndF(effect->root) != 0)
            sEffectPurge(effect);
    }
}
