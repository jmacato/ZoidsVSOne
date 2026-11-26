#include "zoid.h"

extern void ZoidSisei(ZoidState *zoid);
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 zdColPosY(Vec3 *point, u16 *selector);

void ZoidSusumuV(ZoidState *zoid)
{
    f32 length;
    f32 x;
    f32 y;
    f32 z;
    f32 depth;
    u16 selector;
    s32 frame_padding[13];

    if (zoid != 0 && zoid->joint != 0) {
        ZoidSisei(zoid);
        length = sLenPoint3dR(&zoid->launch_velocity);
        if (length > 0.8) {
            x = 0.8 * zoid->launch_velocity.x / length;
            y = 0.8 * zoid->launch_velocity.y / length;
            z = 0.8 * zoid->launch_velocity.z / length;
        } else {
            x = zoid->launch_velocity.x;
            y = zoid->launch_velocity.y;
            z = zoid->launch_velocity.z;
        }
        zoid->position[0] += x;
        zoid->position[1] += y;
        zoid->position[2] += z;
        zoid->launch_velocity.y -= 0.04;
        length = sLenPoint3dR(&zoid->launch_velocity);
        if (length > 0.8) {
            zoid->launch_velocity.x = 0.8 * zoid->launch_velocity.x / length;
            zoid->launch_velocity.y = 0.8 * zoid->launch_velocity.y / length;
            zoid->launch_velocity.z = 0.8 * zoid->launch_velocity.z / length;
        }
        depth = zdColPosY((Vec3 *)zoid->position, &selector) - zoid->position[1];
        if (depth > 0.0f) {
            zoid->height_offset_speed = 0.0f;
            zoid->height_offset -= depth;
            zoid->position[1] += depth;
        }
        zoid->ground_polygon = selector;
    }
}
