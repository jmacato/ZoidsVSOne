#include "types.h"

s32 chkLineX(Vec3 *first, Vec3 *second, f32 x)
{
    f32 low = first->x;
    f32 high = second->x;
    f32 temporary;

    if (low > high) {
        temporary = low;
        low = high;
        high = temporary;
    }
    if (x < low) {
        return 0;
    }
    if (high < x) {
        return 0;
    }
    return 1;
}
