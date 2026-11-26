#include "zoid_collision.h"
#include "ground_collision.h"
#include "matrix.h"

extern s32 sCubeInPoly(s32 count, Vec3 *vertices);

s32 zdGrdCoPo00(CoObj *object, GroundPolygon *polygon)
{
    Vec3 local[4];
    s32 count;
    s32 i;

    if (object == 0)
        return 0;
    count = polygon->vertex_count;
    for (i = 0; i < count; i++) {
        Vec3 *vertex = &grdcVtx[polygon->vertices[i]];
        PSMTXMultVec(object->inverse, vertex, &local[i]);
    }
    return sCubeInPoly(count, local);
}
