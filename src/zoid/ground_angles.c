#include "zoid.h"

extern f32 zdGoYA3d(ZoidState *zoid, f32 *point);

f32 zdGoYA3dOfstBy(ZoidState *zoid, f32 *offset, f32 fraction)
{
    f32 point[3];
    s32 axis;

    for (axis = 0; axis < 3; axis++)
        point[axis] = zoid->position[axis] + fraction * offset[axis];
    return zdGoYA3d(zoid, point);
}
