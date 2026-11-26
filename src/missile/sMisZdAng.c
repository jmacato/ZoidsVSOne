#include "zoid.h"
#include "missile.h"
#include "math_support.h"

extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);

static inline f32 MisKeep(f32 value)
{
    f32 t[1];

    t[0] = value;
    return t[0];
}

f32 sMisZdAng(ZoidState *zoid, f32 *angle)
{
    Missile *missile;
    f32 nearest;
    f32 dx;
    f32 dz;
    f32 length;
    f32 dy;
    s32 i;
    s32 k;
    s32 frame_padding[2];
    Vec3 point;

    nearest = -1.0f;
    if (zoid == 0)
        return nearest;
    if (zoid->joint == 0)
        return nearest;
    missile = missileStart;
    for (i = 0; i < 200; i++, missile++) {
        if (!(missile->flags & MISSILE_FLAG_ACTIVE))
            continue;
        if (missile->purge_timer != 0)
            continue;
        if (missile->hit != 0)
            continue;
        if (missile->joint == 0)
            continue;
        if (missile->field_30 != 0)
            continue;
        if (missile->target_zoid == 0)
            continue;
        if (missile->target_zoid->joint == 0)
            continue;
        if (missile->target_zoid != zoid)
            continue;
        length = 0.0f;
        dx = zoid->position[0] - missile->matrix[0][3];
        length += dx * dx;
        dy = zoid->position[1] - missile->matrix[1][3];
        length += dy * dy;
        dz = zoid->position[2] - missile->matrix[2][3];
        length += dz * dz;
        length = square_root(length);
        if (nearest > length || nearest == -1.0f)
            nearest = MisKeep(length);
    }
    if (angle == 0 || missile == 0)
        return nearest;
    point.x = missile->joint->matrix[0][3];
    point.y = missile->joint->matrix[1][3];
    point.z = missile->joint->matrix[2][3];
    *angle = ZoidCalcAngle(zoid, &point);
    return nearest;
}
