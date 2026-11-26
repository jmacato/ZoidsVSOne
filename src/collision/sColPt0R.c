#include "ground_collision.h"

#define NULL 0

extern s32 sLineSurface(f32 *start, f32 *end, Vec3 *points, s32 count);
extern f32 sLiner(f32 target, f32 current, f32 fraction);

static inline f32 fabsf(f32 value)
{
    return (*(u32 *)&value &= 0x7FFFFFFF, value);
}

f32 sColPt0R(Vec3 *point, Vec3 *unused, GroundPolygon *polygon, GroundMask mask, f32 radius)
{
    Vec3 pad_stack[3];
    Vec3 points[4];
    f32 front[3];
    f32 back[3];
    f32 pad_word;
    f32 *normal;
    GroundMask *material;
    f32 front_distance;
    f32 back_distance;
    f32 fraction;
    s32 same;
    s32 i;

    if (polygon == NULL)
        return GROUND_NO_HIT;
    material = &grdcMat[polygon->material];
    normal = &grdcNormal[polygon->normal_index].x;
    for (i = 0; i < 3; i++) {
        front[i] = radius * normal[i] + (&point->x)[i];
        back[i] = (&point->x)[i] - radius * normal[i];
    }
    if (!(material->bits[0] & mask.bits[0]) && !(material->bits[1] & mask.bits[1]) &&
        !(material->bits[2] & mask.bits[2]))
        return GROUND_NO_HIT;
    front_distance = polygon->plane_offset +
                     (polygon->normal.x * front[0] + polygon->normal.y * front[1] + polygon->normal.z * front[2]);
    back_distance = polygon->plane_offset +
                    (polygon->normal.x * back[0] + polygon->normal.y * back[1] + polygon->normal.z * back[2]);
    if (front_distance * back_distance > 0.0f)
        return GROUND_NO_HIT;
    same = 0;
    fraction = fabsf(front_distance) / fabsf(front_distance - back_distance);
    for (i = 0; i < 3; i++) {
        if (front[i] == back[i])
            same++;
    }
    if (same == 3)
        return GROUND_NO_HIT;
    for (i = 0; i < polygon->vertex_count; i++) {
        points[i].x = grdcVtx[polygon->vertices[i]].x;
        points[i].y = grdcVtx[polygon->vertices[i]].y;
        points[i].z = grdcVtx[polygon->vertices[i]].z;
    }
    if (sLineSurface(front, back, points, polygon->vertex_count) == 0)
        return GROUND_NO_HIT;
    for (i = 0; i < 3; i++)
        (&point->x)[i] = sLiner(back[i], front[i], fraction) + radius * normal[i];
    return fraction;
}
