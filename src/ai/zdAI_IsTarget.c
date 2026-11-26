#include "zoid_ai.h"

s32 zdAI_IsTarget(s32 index)
{
    ZoidState *zoid;

    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return 0;
    }
    if (zoid->target_pending == 0) {
        return 0;
    }
    return 1;
}
