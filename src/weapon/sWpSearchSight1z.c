#include "weapon.h"
#include "zoid.h"
#include "game_camera.h"

s32 sWpSearchSight1z(WeaponState *weapon, ZoidState *zoid, ZoidState *target)
{
    s32 i;
    s32 count;
    WeaponMarker *marker;
    s32 pt[3];

    if (target == 0)
        return 0;
    if (target->joint == 0)
        return 0;
    count = weapon->marker_count;
    if (count < 1)
        return 1;
    for (i = 0; i < count; i++) {
        marker = &weapon->markers[i];
        if (marker->joint != 0 && marker->target == target)
            return 0;
    }
    for (i = 0; i < count; i++) {
        marker = &weapon->markers[i];
        if (marker->joint == 0)
            break;
    }
    if (i == count)
        return 1;
    if (weapon->range < zoid->distances[target->index])
        return 0;
    if (zoid->camera != 0 && sCameraPt2d(zoid->camera, (Vec3 *)target->position, pt) == 0)
        return 0;
    marker->target = target;
    marker->locked = 0;
    marker->joint = target->camera_joint;
    marker->source = 0;
    for (i = 0; i < 3; i++) {
        (&marker->position.x)[i] = target->camera_joint->matrix[i][3];
    }

    marker->position.y -= 50.0f;
    return 0;
}
