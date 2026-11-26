#include "ground_collision.h"

extern s32 chkLineX(Vec3 *first, Vec3 *second, f32 x);
extern f32 calLineY(Vec3 *first, Vec3 *second, Vec3 *third, Vec3 *point);

f32 sColGetPolyY(u16 index, Vec3 *point)
{
    GroundPolygon *polygon;
    u16 *vertices;
    f32 x = point->x;

    if (index == GROUND_POLYGON_NONE)
        return point->y;
    polygon = &grdcPolygon[index];
    vertices = polygon->vertices;
    if (!chkLineX(&grdcVtx[vertices[0]], &grdcVtx[vertices[1]], x)) {
        if (!chkLineX(&grdcVtx[vertices[1]], &grdcVtx[vertices[2]], x))
            return point->y;
        if (!chkLineX(&grdcVtx[vertices[2]], &grdcVtx[vertices[0]], x))
            return point->y;
        return calLineY(&grdcVtx[vertices[1]], &grdcVtx[vertices[2]],
                        &grdcVtx[vertices[0]], point);
    }
    if (chkLineX(&grdcVtx[vertices[1]], &grdcVtx[vertices[2]], x))
        return calLineY(&grdcVtx[vertices[0]], &grdcVtx[vertices[1]],
                        &grdcVtx[vertices[2]], point);
    if (!chkLineX(&grdcVtx[vertices[2]], &grdcVtx[vertices[0]], x))
        return point->y;
    return calLineY(&grdcVtx[vertices[2]], &grdcVtx[vertices[0]],
                    &grdcVtx[vertices[1]], point);
}
