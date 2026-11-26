#include "ground_collision.h"

GroundPolygon *sColBallYH(Vec3 *point, GroundMask *mask, s32 mode, f32 radius)
{
    Vec3 weights = {1.f, 2.f, 1.f};
    return sColBallH3(point, &weights, mask, mode, radius);
}
