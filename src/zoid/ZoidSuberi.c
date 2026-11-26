#include "zoid.h"

extern f32 cosf(f32 angle);
extern f32 sinf(f32 angle);

void ZoidSuberi(ZoidState *zoid)
{
    f64 scale = 1.5;

    if (zoid != 0 && zoid->joint != 0) {
        zoid->slide_frames++;
        if (zoid->slide_speed == 0.0f) {
            zoid->slide_frames = 0;
            return;
        }
        zoid->position[0] -= scale * (zoid->slide_speed * cosf(-zoid->heading));
        zoid->position[2] -= scale * (zoid->slide_speed * sinf(-zoid->heading));
    }
}
