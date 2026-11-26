#include "types.h"

extern void ssLoadStageNow(s32 stage, s32 mode);

void LoadStageNow(s32 stage)
{
    ssLoadStageNow(stage, 0);
}
