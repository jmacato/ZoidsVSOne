#include "zoid.h"

void ik3dAnim(ZoidState *zoid, FootJoint *foot)
{
    if (zoid == 0)
        return;
    if (foot == 0)
        return;
    if (foot->joint == 0)
        return;
    foot->height = foot->joint->matrix[1][3];
}
