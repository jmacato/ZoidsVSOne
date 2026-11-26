#include "zoid.h"

void chkDeep(FootJoint *foot, s32 *found, f32 *minimum)
{
    f32 depth;

    if (foot->depth > 0.0f) {
        *found = 1;
        depth = foot->depth;
        if (depth < *minimum) {
            *minimum = depth;
        }
    }
}
