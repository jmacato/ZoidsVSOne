#include "zoid.h"
#include "ground_collision.h"

extern s32 zdGroundPoly(ZoidState *zoid, s32 index, GroundPolygon *polygon);

static inline GroundMask *groundMat(u16 index)
{
    GroundPolygon *polygon = grdcPolygon;
    GroundMask *mask;
    polygon += index;
    mask = &grdcMat[polygon->material];
    return mask;
}

s32 zdGroundTBL(ZoidState *zoid, u16 *table)
{
    u16 index;

    while (1) {
        index = *table++;
        if (index == GROUND_POLYGON_NONE) {
            return 0;
        }
        if ((groundMat(index)->bits[0] & 0x1F) != 0) {
            zdGroundPoly(zoid, index, &grdcPolygon[index]);
        }
    }
}
