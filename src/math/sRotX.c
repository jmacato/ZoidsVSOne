#include "types.h"

void sRotX(Vec3 *point, f32 cosine, f32 sine)
{
    f32 z = point->z;
    f32 y = point->y;

    point->y = cosine * y - sine * z;
    point->z = sine * y + cosine * z;
}
