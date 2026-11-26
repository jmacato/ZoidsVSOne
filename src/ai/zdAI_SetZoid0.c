#include "zoid_ai.h"

void zdAI_SetZoid0(s32 index, s32 target)
{
    ZoidAIState *ai;
    ZoidState *zoid;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0 && target != -1 && Zoid[target].joint != 0) {
            ai = zoid->ai;
            if (ai != 0) {
                ai->target_index = target;
                ai->mode = AI_MODE_TARGET;
                ai->flags = 0;
            }
        }
    }
}
