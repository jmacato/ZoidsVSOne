#include "zoid.h"
#include "math_support.h"

#pragma auto_inline off

extern void zdAtk(ZoidState *zoid);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);

void zdLen(s32 first, s32 second)
{
    f32 difference;
    f32 length = 0.0f;
    s32 axis;

    if (first != second) {
        for (axis = 0; axis < 3; axis++) {
            difference = Zoid[first].joint->matrix[axis][3] - Zoid[second].joint->matrix[axis][3];
            length += difference * difference;
        }
        length = square_root(length);
    }
    Zoid[first].distances[second] = length;
    Zoid[second].distances[first] = length;
}

void ZoidLen(void)
{
    s32 first, second;
    f32 angle;

    for (first = 0; first < 16; first++) {
        if (Zoid[first].joint != 0) {
            for (second = first; second < 16; second++) {
                if (Zoid[second].joint != 0)
                    zdLen(first, second);
            }
        }
    }
    for (first = 0; first < 16; first++) {
        if (Zoid[first].joint != 0) {
            zdAtk(&Zoid[first]);
            for (second = 0; second < 16; second++) {
                if (first != second && Zoid[second].joint != 0) {
                    angle = ZoidCalcAngle(&Zoid[first], (Vec3 *)Zoid[second].position);
                    if (angle != 100.0)
                        Zoid[first].target_angles[second] = angle;
                }
            }
        }
    }
}
