#include "zoid.h"

s32 zdLakkaTest2(ZoidState *zoid)
{
    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    if ((zoid->movement_flags & 3) != 2) {
        return 0;
    }
    if (zoid->ground_normal_count != 0) {
        return 0;
    }
    return 1;
}
