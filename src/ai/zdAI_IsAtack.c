#include "zoid_ai.h"

s32 zdAI_IsAtack(s32 index)
{
    ZoidState *zoid;
    ZoidState *other;
    s32 i;

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
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other->joint != 0 && zoid->attack_in_range[i] == 1) {
            return 1;
        }
    }
    return 0;
}
