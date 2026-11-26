#include "zoid_ai.h"

void zdAI_SetZoid(s32 index)
{
    ZoidState *zoid;
    ZoidAIState *ai;
    s32 target;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            ai = zoid->ai;
            ai->target_index = target = ai->nearest_enemies[0];
            ai->mode = AI_MODE_TARGET;
            ai->flags = 0;
        }
    }
}
