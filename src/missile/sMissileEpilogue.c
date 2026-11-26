#include "types.h"
#include "model_archive.h"

extern void *missileFile[130];

void sMissileEpilogue(void)
{
    s32 i;
    for (i = 0; i < 130; i++) {
        if (missileFile[i] != 0)
            PurgeArc2(missileFile[i]);
        missileFile[i] = 0;
    }
}
