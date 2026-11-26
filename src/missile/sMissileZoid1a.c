#include "zoid.h"
#include "missile.h"

#define NULL 0

extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern f32 sColCube4LineConnect(Vec3 *first, Vec3 *second);
extern void ZoidCoObjMove(CoObj *object, Vec3 *move);

f32 sMissileZoid1a(Missile *missile, CoObj *object, s32 push)
{
    f32 (*inverse)[4];
    Vec3 current;
    Vec3 previous;
    f32 pad_stack0[2];
    Vec3 move;
    f32 t;
    Vec3 *dir;
    f32 pad_stack1[7];

    if (object == NULL)
        return -1.0f;
    if (object->joint == NULL)
        return -1.0f;
    current.x = missile->matrix[0][3];
    previous.x = missile->previous[0][3];
    current.y = missile->matrix[1][3];
    previous.y = missile->previous[1][3];
    current.z = missile->matrix[2][3];
    previous.z = missile->previous[2][3];
    inverse = object->inverse;
    PSMTXMultVec(inverse, &current, &current);
    PSMTXMultVec(inverse, &previous, &previous);
    t = sColCube4LineConnect(&previous, &current);
    if (-1.0f != t && push != 0) {
        dir = &move;
        dir->x = 2.0f * missile->matrix[0][0];
        dir->y = 2.0f * missile->matrix[1][0];
        dir->z = 2.0f * missile->matrix[2][0];
        ZoidCoObjMove(object, dir);
    }
    return t;
}
