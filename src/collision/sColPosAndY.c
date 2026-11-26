#include "ground_collision.h"

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

f32 sColPosAndY(Vec3 *point, u16 *selector, GroundMask *mask)
{
    u16 *table;
    u16 index;
    u16 best_index;
    GroundPolygon *polygon;
    GroundMask *material;
    f32 y;
    f32 best_y;
    f32 distance;
    f32 best_distance;
    s32 frame_padding[2];

    if (selector != 0)
        *selector = GROUND_POLYGON_NONE;
    table = sColPosTBL(point);
    if (table == 0)
        return point->y;
    best_y = point->y;
    best_index = GROUND_POLYGON_NONE;
    while (1) {
        index = *table;
        if (index == GROUND_POLYGON_NONE)
            break;
        if (sColPosPolygonON(point, index) == 0)
            goto next;
        polygon = &grdcPolygon[index];
        if (grdcNormal[polygon->normal_index].y < 0.0f)
            goto next;
        material = &grdcMat[polygon->material];
        if (!(material->bits[0] & mask->bits[0]) && !(material->bits[1] & mask->bits[1]) &&
            !(material->bits[2] & mask->bits[2]))
            goto next;
        y = sColGetPolyY(index, point);
        distance = absf(y - point->y);
        if (best_index == GROUND_POLYGON_NONE) {
            best_y = y;
            best_index = index;
            best_distance = distance;
        }
        if (best_distance > distance) {
            best_y = y;
            best_index = index;
            best_distance = distance;
        }
    next:
        table++;
    }
    if (selector != 0)
        *selector = best_index;
    return best_y;
}
