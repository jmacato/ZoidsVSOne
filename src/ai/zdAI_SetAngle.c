#include "zoid_ai.h"

void zdAI_SetAngle(s32 index, s32 angle_mode, s32 degrees, s32 speed)
{
    ZoidState *zoid;
    ZoidAIState *ai;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            ai = zoid->ai;
            ai->mode = AI_MODE_TARGET;
            ai->flags = (ai->flags & ~AI_ANGLE_MASK) | (angle_mode << AI_ANGLE_SHIFT);
            ai->target_angle = 2.0 * (3.1415926 * (f32)degrees) / 360.0;
            ai->turn_speed = speed;
        }
    }
}
