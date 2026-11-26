#include "zoid_ai.h"
#include "ground_collision.h"

void zdAI_goPoint(s32 index, f32 x, f32 z)
{
    ZoidState *zoid;
    ZoidAIState *ai;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            ai = zoid->ai;
            if (ai != 0) {
                ai->mode = AI_MODE_POINT;
                ai->flags = AI_RADIUS_IN;
                ai->target_distance = 50.0f;
                ai->destination.x = x;
                ai->destination.z = z;
                ai->destination.y = 100.0f;
                ai->destination.y = sColPosY(&ai->destination, 0);
            }
        }
    }
}
