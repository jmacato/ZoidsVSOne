#include "zoid_ai.h"

s32 zdAI_IsAtackMine(s32 index)
{
    s32 i;
    ZoidState *zoid;

    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    if (Zoid[index].joint == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (i != index && zoid->joint != 0 && zoid->attack_in_range[index] != 0 &&
            zoid->action >= ZOID_ACTION_ATTACK_0 && zoid->action <= ZOID_ACTION_ATTACK_9) {
            return 1;
        }
    }
    return 0;
}
