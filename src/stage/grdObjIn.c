#include "types.h"
#include "missile.h"
#include "ground_object.h"

extern Vec3 objScale[];
extern void PSMTXMultVecArray(f32 m[3][4], Vec3 *src, Vec3 *dst, u32 count);
extern s32 sColCube4Point(Vec3 *point);

s32 grdObjIn(GroundObject *object, Missile *missile)
{
    f32 *scale;
    Vec3 local[2];
    Vec3 points[2];
    f32 unused[2];
    s32 i;
    s32 k;

    if (object->animation != GROUND_OBJECT_ANIM_INTACT)
        return 1;
    scale = &objScale[object->archive_slot].x;
    for (k = 0; k < 3; k++) {
        if (scale[k] == 0.0f)
            return 0;
    }
    for (k = 0; k < 3; k++) {
        (&points[0].x)[k] = missile->matrix[k][3];
        (&points[1].x)[k] = missile->previous[k][3];
    }
    PSMTXMultVecArray(object->inverse, points, local, 2);
    for (i = 0; i < 2; i++) {
        for (k = 0; k < 3; k++)
            (&local[i].x)[k] /= scale[k];
    }
    if (sColCube4Point(&local[0]) == 0 && sColCube4Point(&local[1]) == 0)
        return 0;
    object->health -= missile->damage;
    if (object->health < 0)
        object->health = 0;
    if (object->health > 0)
        return 1;
    grdObjSetAnim(object, GROUND_OBJECT_ANIM_BREAKING);
    return 1;
}
