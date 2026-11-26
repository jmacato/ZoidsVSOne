#include "zoid.h"

extern f32 sLenPoint3dR(f32 *point);

void zdJumpMove(ZoidState *zoid)
{
    s32 axis;
    f32 length;

    length = sLenPoint3dR(zoid->velocity);
    if (length > 1.7) {
        f64 scale = 1.7 / length;
        for (axis = 0; axis < 3; axis++)
            zoid->velocity[axis] *= scale;
    }
    length = sLenPoint3dR(zoid->displacement);
    if (length > 1.7) {
        f64 scale = 1.7 / length;
        for (axis = 0; axis < 3; axis++)
            zoid->displacement[axis] *= scale;
    }
    zoid->velocity[1] -= 0.025;
    zoid->position[0] += zoid->velocity[0];
    zoid->position[1] += zoid->velocity[1];
    zoid->position[2] += zoid->velocity[2];
}
