#include "zoid.h"
#include "ground_collision.h"

extern f32 zdColPosY(Vec3 *point, u16 *selector);
extern void ZoidSisei(ZoidState *zoid);

void ZoidWalkJ(ZoidState *zoid)
{
    f32 dx;
    f32 dz;
    Vec3 position;
    s32 frame_padding;
    u16 selector;

    if (zoid != 0 && zoid->joint != 0) {
        dx = zoid->displacement[0];
        dz = zoid->displacement[2];
        position.x = zoid->position[0] + dx;
        position.y = zoid->position[1];
        position.z = zoid->position[2] + dz;
        zdColPosY(&position, &selector);
        zoid->ground_polygon = selector;
        if (selector == GROUND_POLYGON_NONE) {
            zoid->heading += 3.0f;
        } else {
            zoid->position[0] += dx;
            zoid->position[2] += dz;
            ZoidSisei(zoid);
        }
    }
}
