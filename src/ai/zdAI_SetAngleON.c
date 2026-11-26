#include "zoid_ai.h"

void zdAI_SetAngleON(s32 index, s32 degrees)
{
    zdAI_SetAngle(index, AI_ANGLE_KEEP, degrees, 0);
}
