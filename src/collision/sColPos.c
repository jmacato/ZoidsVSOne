#include "ground_collision.h"

s32 sColPos(Vec3 *point)
{
    f32 x = point->x;
    f32 z = point->z;
    s32 column;
    s32 row;

    if (x < grdcStartX) {
        column = 0;
    } else if (grdcEndX < x) {
        column = grdcDivX - 1;
    } else {
        column = (s32)((x - grdcStartX) / grdcDiffX);
    }
    if (z < grdcStartZ) {
        row = 0;
    } else if (grdcEndZ < z) {
        row = grdcDivZ - 1;
    } else {
        row = (s32)((z - grdcStartZ) / grdcDiffZ);
    }
    return column + row * grdcDivX;
}
