#include "game_camera.h"

extern f32 sLiner(f32 target, f32 current, f32 rate);

void linierCamXZ(CameraState *camera)
{
    s32 i;
    f32 rate = 0.3f;
    s32 frame_padding[2];

    for (i = 0; i < 3; i++) {
        (&camera->interest.x)[i] = sLiner((&camera->focus.x)[i], (&camera->interest.x)[i], rate);
        (&camera->eye.x)[i] = sLiner((&camera->relative_origin.x)[i], (&camera->eye.x)[i], rate);
    }
}
