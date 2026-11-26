#include "zoid.h"
#include "ground_collision.h"

extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern f32 atan2f(f32 y, f32 x);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void PSMTXRotRad(f32 m[3][4], char axis, f32 rad);
extern void PSMTXMultVecSR(f32 m[3][4], Vec3 *src, Vec3 *dst);

f32 zdGoYA(ZoidState *zoid, f32 angle, f32 distance)
{
    f32 origin[3];
    f32 target[3];
    s32 frame_padding[1];
    u16 selector;
    f32 mtx[3][4];
    s32 padB[1];
    Vec3 normal;
    s32 padC[3];
    s32 axis;

    if (zoid == 0)
        return 0.0f;
    if (zoid->joint == 0)
        return 0.0f;
    if (0.0f == distance) {
        Vec3 *ground;
        if (zoid->ground_polygon == GROUND_POLYGON_NONE)
            return 0.0f;
        ground = &grdcNormal[grdcPolygon[zoid->ground_polygon].normal_index];
        PSMTXRotRad(mtx, 'Y', -zoid->heading - angle);
        PSMTXMultVecSR(mtx, ground, &normal);
        {
            f32 y = normal.y;
            return -atan2f(normal.z, y);
        }
    }
    for (axis = 0; axis < 3; axis++) {
        target[axis] = origin[axis] = zoid->position[axis];
    }
    target[1] = origin[1] = zoid->ground_height;
    target[0] += distance * sinf(angle + zoid->heading);
    target[2] += distance * cosf(angle + zoid->heading);
    target[1] = zdColPosY(target, &selector);
    return atan2f(target[1] - origin[1], distance);
}
