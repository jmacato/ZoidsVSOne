#include "zoid.h"

extern void ftSmoke(ZoidState *zoid, FootJoint *foot, s32 frame);

void zdSmoke(ZoidState *zoid)
{
    s32 frame;

    if (zoid != 0 && zoid->joint != 0 && zoid->type != 4) {
        frame = zoid->current_animation;
        if (frame == 1)
            frame = 2;
        ftSmoke(zoid, &zoid->feet[0], 0);
        ftSmoke(zoid, &zoid->feet[1], 0);
        ftSmoke(zoid, &zoid->feet[2], frame);
        ftSmoke(zoid, &zoid->feet[3], frame);
    }
}
