#include "ground_collision.h"

#pragma dont_inline on
static f32 sColPt01(Vec3 *start, Vec3 *end, u16 *indices, GroundMask mask)
{
    f32 fraction;
    if (indices == 0)
        return GROUND_NO_HIT;
    while (*indices != GROUND_POLYGON_NONE) {
        GroundPolygon *polygon = &grdcPolygon[*indices];
        fraction = sColPt00(start, end, polygon, mask);
        if (fraction != GROUND_NO_HIT)
            return fraction;
        indices++;
    }
    return GROUND_NO_HIT;
}

f32 sColPt(Vec3 *start, Vec3 *end, GroundMask mask)
{
    u16 *start_indices = sColPosTBL(start);
    u16 *end_indices = sColPosTBL(end);
    f32 fraction = sColPt01(start, end, start_indices, mask);
    if (fraction != GROUND_NO_HIT)
        return fraction;
    if (start_indices == end_indices)
        return GROUND_NO_HIT;
    {
        return sColPt01(start, end, end_indices, mask);
    }
}

static f32 sColPt01R(Vec3 *point, Vec3 *unused, u16 *indices, GroundMask mask,
                     f32 radius)
{
    f32 fraction;
    if (indices == 0)
        return GROUND_NO_HIT;
    while (*indices != GROUND_POLYGON_NONE) {
        GroundPolygon *polygon = &grdcPolygon[*indices];
        fraction = sColPt0R(point, unused, polygon, mask, radius);
        if (fraction != GROUND_NO_HIT)
            return fraction;
        indices++;
    }
    return GROUND_NO_HIT;
}

f32 sColPtR(Vec3 *point, Vec3 *unused, GroundMask mask, f32 radius)
{
    u16 *indices = sColPosTBL(point);
    f32 fraction = sColPt01R(point, unused, indices, mask, radius);
    if (fraction != GROUND_NO_HIT)
        return fraction;
    return GROUND_NO_HIT;
}
