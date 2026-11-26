#include "zoid.h"

extern f32 sLenJobj(HSD_JObj *first, HSD_JObj *second);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);
extern void angLimit(f32 *angle);

void zdAtkSubFor(ZoidState *zoid)
{
    ZoidState *target;
    f32 angle;
    s8 slot;

    if (zoid != 0 && zoid->joint != 0) {
        slot = zoid->attack_target;
        if (slot != -1) {
            target = &Zoid[slot];
            if (target->joint != 0 && !(sLenJobj(zoid->joint->child, target->joint->child) < 8.0f)) {
                angle = ZoidCalcAngle(zoid, (Vec3 *)target->position);
                if (angle > 2.0 * 3.1415926 * 3.0 / 360.0) {
                    angle = 2.0 * 3.1415926 * 3.0 / 360.0;
                }
                if (angle < -(2.0 * 3.1415926 * 3.0 / 360.0)) {
                    angle = -(2.0 * 3.1415926 * 3.0 / 360.0);
                }
                zoid->heading += angle;
                angLimit(&zoid->heading);
            }
        }
    }
}
