#include "zoid_collision.h"

extern u32 PSMTXInverse(f32 src[3][4], f32 dst[3][4]);

void zdCoObjMtxI(CoObj *object)
{
    if (object != 0 && object->joint != 0)
        PSMTXInverse(object->joint->matrix, object->inverse);
}
