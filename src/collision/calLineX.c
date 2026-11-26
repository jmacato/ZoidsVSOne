#include "types.h"

void calLineX(f32 *first, f32 *second, f32 *point, f32 *output)
{
    s32 axis;
    f32 delta[3];
    f32 fraction;

    if (point[0] == first[0]) {
        for (axis = 0; axis < 3; axis++)
            output[axis] = first[axis];
        return;
    }
    if (point[0] == second[0]) {
        for (axis = 0; axis < 3; axis++)
            output[axis] = second[axis];
        return;
    }
    for (axis = 0; axis < 3; axis++)
        delta[axis] = second[axis] - first[axis];
    fraction = point[0] - first[0];
    if (fraction == 0.0F || delta[0] == 0.0F) {
        for (axis = 0; axis < 3; axis++)
            output[axis] = first[axis];
        return;
    }
    fraction /= delta[0];
    for (axis = 0; axis < 3; axis++)
        output[axis] = first[axis] + fraction * delta[axis];
}
