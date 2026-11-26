#include "zoid_ai.h"

void zdAI_SetLockZoid(s32 index)
{
    ZoidState *zoid;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            zdAI_SetZoid0(index, zoid->target_slot);
        }
    }
}
