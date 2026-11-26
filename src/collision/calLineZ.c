#include "types.h"

f32 calLineZ(f32 *first, f32 *second, f32 *point)
{
    f32 delta[3];
    f32 distance;
    s32 axis;

    if (point[2] == first[2])
        return first[1];
    if (point[2] == second[2])
        return second[1];
    for (axis = 0; axis < 3; axis++)
        delta[axis] = second[axis] - first[axis];
    distance = point[2] - first[2];
    if (distance == 0.0F || delta[2] == 0.0F)
        return first[1];
    return first[1] + delta[1] * (distance / delta[2]);
}
