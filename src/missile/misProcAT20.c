#include "missile.h"
#include "matrix.h"
#include "joint_matrix.h"

extern void PSMTXRotRad(Mtx m, char axis, f32 rad);

void misProcAT20(Missile *missile, Vec3 *target)
{
    Vec3 local;
    Mtx rot;
    f32 angle;

    PSMTXMultVec(missile->inverse, target, &local);
    angle = 0.0f;
    if (local.z > angle) {
        angle = -missile->turn_rate;
    }
    if (angle != 0.0f) {
        PSMTXRotRad(rot, 'Y', angle);
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
    angle = 0.0f;
    if (local.y > angle) {
        angle = -DEG2RAD_F(10.0f);
    }
    if (local.y < 0.0f) {
        angle = DEG2RAD_F(10.0f);
    }
    if (angle != 0.0f) {
        while (angle) {
            PSMTXRotRad(rot, 'X', angle);
            PSMTXConcat(missile->matrix, rot, missile->matrix);
            PSMTXMultVec(missile->inverse, target, &local);
            angle *= 0.5f;
            if (local.y == 0.0f) {
                break;
            }
            if (local.y > 0.0f && angle > 0.0f) {
                angle = -angle;
            }
            if (local.y < 0.0f && angle < 0.0f) {
                angle = -angle;
            }
        }
    }
}
