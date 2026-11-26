#include "zoid_ai.h"

extern f32 zdGoY(ZoidState *zoid, f32 angle, f32 distance);

f32 zdAI_goY(s32 index, s32 degrees, f32 distance)
{
    ZoidState *zoid;

    if (index < 0) {
        return 0.0f;
    }
    if (index >= 16) {
        return 0.0f;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return 0.0f;
    }
    return zdGoY(zoid, (f32)((2.0 * (3.1415926 * (f64)(f32)degrees)) / 360.0), distance);
}
