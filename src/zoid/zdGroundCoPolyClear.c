#include "zoid.h"
#include "ground_collision.h"

void zdGroundCoPolyClear(ZoidState *zoid, CoObj *poly)
{
    if (zoid == 0)
        return;
    if (poly->joint == 0)
        return;
    poly->ground_polygon_index = GROUND_POLYGON_NONE;
    poly->ground_contact = 0;
    poly->object_contact = 0;
}
