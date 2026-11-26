#include "game_camera.h"
#include "math_support.h"

void sCamBallOut(CameraState *camera, f32 radius)
{
    f32 length;
    f32 delta[3];
    s32 axis;

    for (axis = 0; axis < 3; axis++)
        delta[axis] = (&camera->interest.x)[axis] - (&camera->relative_origin.x)[axis];
    length = square_root(delta[0] * delta[0] + delta[2] * delta[2]);
    if (length > radius)
        return;
    if (length != 0.0f) {
        for (axis = 0; axis < 3; axis++) {
            if (axis != 1)
                (&camera->interest.x)[axis] = (&camera->relative_origin.x)[axis] + radius * delta[axis] / length;
        }
    }
}
