#include "zoid_ai.h"

extern s32 zdFaceAtk(ZoidState *zoid, f32 distance);

s32 zdAI_goWall(s32 index, s32 distance)
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
    return zdFaceAtk(zoid, (f32)distance);
}
