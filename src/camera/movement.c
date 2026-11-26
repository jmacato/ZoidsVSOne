#include "game_camera.h"


s32 linierCamLimitXZ(CameraState *camera, f32 radius)
{
    Vec3 *interest = &camera->interest;
    Vec3 *eye = &camera->eye;
    Vec3 *origin = &camera->relative_origin;
    Vec3 *focus = &camera->focus;
    f32 limit = radius * radius;
    f32 x, y, z;
    z = origin->z - eye->z;
    x = origin->x - eye->x;
    y = origin->y - eye->y;
    if (x * x + z * z + y * y > limit)
        return 1;
    z = focus->z - interest->z;
    x = focus->x - interest->x;
    y = focus->y - interest->y;
    if (x * x + z * z + y * y > limit / 2.0F / 2.0F)
        return 1;
    return 0;
}

