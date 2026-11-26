#include "zoid_ai.h"

void zdAI_Run(s32 index, s32 degrees)
{
    ZoidState *zoid;
    ZoidAIState *ai;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            ai = zoid->ai;
            ai->mode = AI_MODE_RUN;
            ai->flags = 0;
            ai->turn_speed = (s32)(2.0 * (3.1415926 * (f32)degrees) / 360.0);
        }
    }
}
