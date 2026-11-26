#include "types.h"

extern void calLineX(f32 *first, f32 *second, f32 *point, f32 *result);
extern f32 calLineZ(f32 *first, f32 *second, f32 *point);

f32 calLineY(Vec3 *first, Vec3 *second, Vec3 *third, Vec3 *point)
{
    Vec3 first_crossing;
    Vec3 second_crossing;

    calLineX((f32 *)first, (f32 *)second, (f32 *)point, (f32 *)&first_crossing);
    calLineX((f32 *)second, (f32 *)third, (f32 *)point, (f32 *)&second_crossing);
    return calLineZ((f32 *)&first_crossing, (f32 *)&second_crossing, (f32 *)point);
}
