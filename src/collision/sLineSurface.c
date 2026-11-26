#include "types.h"

extern void sLineRotYX(Vec3 *origin, Vec3 *end, Vec3 *point);
extern s32 sLineSurface00(f32 edge_x, f32 edge_y, f32 offset_x, f32 offset_y);

/* nonzero when the line start-end passes inside the convex polygon points[count] */
s32 sLineSurface(Vec3 *start, Vec3 *end, Vec3 *points, s32 count)
{
    s32 i;
    s32 negative_edges;

    for (i = 0; i < count; i++)
        sLineRotYX(start, end, &points[i]);
    for (i = 0, negative_edges = 0; i < count; i++) {
        f32 y;
        f32 x;
        f32 ny;
        f32 nx;

        x = points[i].x;
        y = points[i].y;
        nx = points[(i + 1) % count].x;
        ny = points[(i + 1) % count].y;
        if (sLineSurface00(nx - x, ny - y, -x, -y) == 0)
            negative_edges++;
    }
    if (negative_edges == 0 || negative_edges == count)
        return 1;
    return 0;
}
