#include "zoid.h"
#include "game_pad.h"

extern PadState *sPad1;
extern f32 menuzoidry;
extern f32 lookCamY;
extern void angLimit(f32 *angle);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

f32 rPadX(void)
{
    f32 ry = menuzoidry;
    f32 floor = 0.0f;
    f32 stick;

    if (Zoid[0].joint != 0 && Zoid[0].head_coobj.joint != 0)
        floor = Zoid[0].head_coobj.joint->matrix[1][3];
    stick = sPad1->substick_y;
    if (stick > 0.35)
        lookCamY += 0.1;
    if (stick < -0.35)
        lookCamY -= 0.1;
    if (absf(stick) < 0.2) {
        if (lookCamY > floor) {
            lookCamY -= 0.01;
            if (lookCamY < floor)
                lookCamY = floor;
        }
        if (lookCamY < floor) {
            lookCamY += 0.01;
            if (lookCamY > floor)
                lookCamY = floor;
        }
    }
    if (lookCamY < 0.0f)
        lookCamY = 0.0f;
    if (lookCamY > 20.0f)
        lookCamY = 20.0f;
    stick = sPad1->substick_x;
    if (stick > 0.35)
        ry += 2.0 * 3.1415926 * 0.5 / 360.0;
    if (stick < -0.35)
        ry -= 2.0 * 3.1415926 * 0.5 / 360.0;
    angLimit(&ry);
    if (ry > 2.0 * 3.1415926 * 60.0 / 360.0)
        ry = 2.0 * 3.1415926 * 60.0 / 360.0;
    if (ry < -(2.0 * 3.1415926 * 60.0 / 360.0))
        ry = -(2.0 * 3.1415926 * 60.0 / 360.0);
    return menuzoidry = ry;
}
