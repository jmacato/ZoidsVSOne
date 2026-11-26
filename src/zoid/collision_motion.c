#include "zoid.h"
#include "zoid_collision.h"
#include "matrix.h"

extern u32 PSMTXInverse(Mtx source, Mtx destination);
extern void sGlobal2Local(HSD_JObj *joint);

void ZoidCoBAK(ZoidState *zoid, CoObj *object)
{
    s32 axis;

    if (zoid == 0)
        return;
    if (object == 0)
        return;
    if (object->joint == 0)
        return;
    for (axis = 0; axis < 3; axis++) {
        object->movement[axis] = object->joint->matrix[axis][3] - object->position[axis];
        object->position[axis] = object->joint->matrix[axis][3];
        if (object->base_joint != 0)
            object->base_position[axis] = object->base_joint->matrix[axis][3];
    }
}

void ZoidCoObjMove(CoObj *object, f32 *movement)
{
    MtxPtr world;
    MtxPtr base;
    s32 axis;

    if (object != 0 && object->joint != 0 && object->base_joint != 0) {
        world = object->joint->matrix;
        base = object->base_joint->matrix;
        for (axis = 0; axis < 3; axis++) {
            world[axis][3] += movement[axis];
            base[axis][3] += movement[axis];
        }
        PSMTXInverse(world, object->inverse);
        sGlobal2Local(object->base_joint);
        object->health -= 20;
        if (object->health < 0)
            object->health = 0;
    }
}
