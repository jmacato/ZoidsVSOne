#include "ground_collision.h"

s32 sColPosPolygonON(Vec3 *point, u16 index)
{
    GroundPolygon *polygon = &grdcPolygon[index];
    s32 i;
    f32 first_x, first_z;
    s32 count = polygon->vertex_count;
    u16 *vertices = polygon->vertices;
    f32 point_x, point_z;

    if (index == GROUND_POLYGON_NONE)
        return 0;
    point_x = point->x;
    point_z = point->z;
    for (i = 0; i < count; i++) {
        Vec3 *first = &grdcVtx[vertices[i]];
        Vec3 *second = &grdcVtx[vertices[(i + 1) % count]];
        f32 x, z, edge_x, edge_z;
        first_x = first->x;
        first_z = first->z;
        x = point_x - first_x;
        z = point_z - first_z;
        edge_x = second->x - first_x;
        edge_z = second->z - first_z;
        if (x * edge_z - z * edge_x > 0.f)
            return 0;
    }
    return 1;
}
