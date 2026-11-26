#include "ground_collision.h"

#define NULL 0

extern f64 __frsqrte(f64);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

GroundPolygon *sColBallH3(Vec3 *point, Vec3 *weights, GroundMask *mask, s32 mode, f32 radius)
{
    u16 *table;
    GroundPolygon *polygon;
    GroundMask *material;
    Vec3 *vertex;
    Vec3 *normal;
    f32 radius_sq;
    f32 distance_sq;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 push;
    s32 i;
    s32 k;
    f32 delta;
    volatile f32 root;
    s32 unused[1];

    radius_sq = radius * radius;
    table = sColPosTBL(point);
    if (table == NULL)
        return NULL;
    while (*table != GROUND_POLYGON_NONE) {
        polygon = &grdcPolygon[*table];
        material = &grdcMat[polygon->material];
        if ((material->bits[0] & mask->bits[0]) || (material->bits[1] & mask->bits[1]) || (material->bits[2] & mask->bits[2])) {
            for (i = 0; i < polygon->vertex_count; i++) {
                vertex = &grdcVtx[polygon->vertices[i]];
                distance_sq = 0.0f;
                for (k = 0; k < 3; k++) {
                    delta = (&point->x)[k] - (&vertex->x)[k];
                    distance_sq += delta * delta * (&weights->x)[k];
                }
                if (!(distance_sq >= radius_sq)) {
                    if ((mode & GROUND_BALL_PUSH_OUT) == 0)
                        return polygon;
                    push = radius - sqrtf(distance_sq, &root);
                    normal = &grdcNormal[polygon->normal_index];
                    for (k = 0; k < 3; k++)
                        (&point->x)[k] += push * (&normal->x)[k];
                }
            }
        }
        table++;
    }
    return NULL;
}
