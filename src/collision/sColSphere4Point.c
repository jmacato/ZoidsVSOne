#include "types.h"

s32 sColSphere4Point(Vec3 *point)
{
    f32 x = point->x * point->x;
    f32 y = point->y * point->y;
    f32 z = point->z * point->z;

    if (z + (x + y) > 0.25) {
        return 0;
    }
    return 1;
}
