#include "zoid_ai.h"

void zdAI_Jump(s32 index)
{
    ZoidState *zoid;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            zoid->requested_action = ZOID_ACTION_JUMP_2;
        }
    }
}
