#include "zoid_ai.h"

void zdAI_SetAngleSpd(s32 index, s32 speed)
{
    zdAI_SetAngle(index, AI_ANGLE_CIRCLE, 0, speed);
}
