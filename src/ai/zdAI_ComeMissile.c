#include "zoid_ai.h"

extern f32 sMisZd(ZoidState *zoid);

f32 zdAI_ComeMissile(s32 index)
{
    ZoidState *zoid;

    if (index < 0) {
        return -1.0f;
    }
    if (index >= 16) {
        return -1.0f;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return -1.0f;
    }
    return sMisZd(zoid);
}
