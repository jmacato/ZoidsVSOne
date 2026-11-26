#include "zoid_ai.h"

void zdAI_SetLen1(s32 index, u32 radius_mode, f32 distance)
{
    ZoidAIState *ai;

    if (index < 0) {
        return;
    }
    if (index >= 16) {
        return;
    }
    if (Zoid[index].joint == 0) {
        return;
    }
    ai = Zoid[index].ai;
    ai->target_distance = distance;
    ai->flags = (ai->flags & ~AI_RADIUS_MASK) | radius_mode;
}
