#include "zoid.h"

void zdAtkSub(ZoidState *zoid)
{
    s32 i;
    f32 distance;
    f32 best;

    if (zoid != 0 && zoid->joint != 0) {
        best = -1.0f;
        for (i = 0; i < 16; i++) {
            if (Zoid[i].joint != 0 && zoid->attack_in_range[i] != 0 && !(zoid->distances[i] <= 0.0f)) {
                if (best == -1.0f || distance > zoid->distances[i]) {
                    distance = zoid->distances[i];
                    best = i;
                }
            }
        }
        zoid->attack_target = best;
    }
}
