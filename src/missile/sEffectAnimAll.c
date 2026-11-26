#include "missile.h"

extern void sEffectAnim1(Effect *effect);
extern void sEffectMove(Effect *effect);

void sEffectAnimAll(void)
{
    s32 i;
    for (i = 0; i < 100; i++) {
        if (sEffect[i].root != 0) {
            sEffectAnim1(&sEffect[i]);
            if (sEffect[i].root != 0)
                sEffectMove(&sEffect[i]);
        }
    }
}
