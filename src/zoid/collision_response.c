#include "zoid.h"

extern f32 sLenPoint3dR(f32 *vector);
extern void ZoidInertia(ZoidState *zoid);

void coBakAtk(ZoidState *zoid)
{
    s32 axis;
    f32 length;

    for (axis = 0; axis < 3; axis++)
        zoid->displacement[axis] = zoid->body_coobj.movement[axis];
    length = sLenPoint3dR(zoid->displacement);
    if (length > 0.9) {
        f64 factor = 0.9 / length;
        for (axis = 0; axis < 3; axis++)
            zoid->displacement[axis] *= factor;
    }
    ZoidInertia(zoid);
}

void ZoidInertia(ZoidState *zoid)
{
    s32 axis;
    f32 length;

    if (zoid != 0 && zoid->joint != 0) {
        zoid->displacement[1] -= 0.025;
        if (zoid->grounded != 0) {
            for (axis = 0; axis < 3; axis++) {
                if (axis == 1)
                    zoid->displacement[1] -= 0.005000000000000001;
                zoid->displacement[axis] *= 0.9;
            }
        }
        length = sLenPoint3dR(zoid->displacement);
        if (length > 0.55) {
            for (axis = 0; axis < 3; axis++)
                zoid->displacement[axis] = 0.55 * zoid->displacement[axis] / length;
        }
        for (axis = 0; axis < 3; axis++)
            zoid->position[axis] += zoid->displacement[axis];
    }
}

void ZoidInertiaAtk(ZoidState *zoid)
{
    s32 axis;
    f32 length;

    if (zoid != 0 && zoid->joint != 0) {
        zoid->displacement[1] -= 0.025;
        if (zoid->grounded != 0) {
            for (axis = 0; axis < 3; axis++) {
                if (axis == 1)
                    zoid->displacement[1] -= 0.005000000000000001;
                zoid->displacement[axis] *= 0.9;
            }
        }
        length = sLenPoint3dR(zoid->displacement);
        if (length > 0.85) {
            for (axis = 0; axis < 3; axis++)
                zoid->displacement[axis] = 0.85 * zoid->displacement[axis] / length;
        }
        for (axis = 0; axis < 3; axis++)
            zoid->position[axis] += zoid->displacement[axis];
    }
}
