#include "zoid_ai.h"
#include "ground_collision.h"

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

static inline GroundMask *groundMat(s32 index)
{
    return &grdcMat[grdcPolygon[index].material];
}

s32 zdAI_WarningArea(s32 index)
{
    ZoidState *zoid;
    s32 polygon_index;
    GroundMask *mask;
    GroundPolygon *polygon;

    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return 0;
    }
    if (absf(zoid->joint->matrix[0][3]) > 2900.0f) {
        return 1;
    }
    if (absf(zoid->joint->matrix[2][3]) > 2900.0f) {
        return 1;
    }
    polygon_index = zoid->ground_polygon;
    if (polygon_index == GROUND_POLYGON_NONE) {
        return 0;
    }
    mask = groundMat(polygon_index);
    if (mask->bits[0] & 6) {
        zoid->field_1B94++;
    } else {
        zoid->field_1B94 = 0;
    }
    if (zoid->field_1B94 > 120) {
        return 1;
    }
    if (mask->bits[0] & 4) {
        return 1;
    }
    return 0;
}
