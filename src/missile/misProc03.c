#include "missile.h"
#include "matrix.h"
#include "joint_matrix.h"
#include "random.h"

extern void PSMTXRotRad(Mtx m, char axis, f32 rad);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void misProc03(Missile *missile, Vec3 *target)
{
    Vec3 local;
    Mtx rot;
    f32 angle;
    s32 elapsed = missile->update_count - missile->proc_delay;

    PSMTXMultVec(missile->inverse, target, &local);
    if (elapsed < 60) {
        if (elapsed % 15 == 0 && local.x < 0.0f) {
            PSMTXRotRad(rot, 'Z', DEG2RAD_F(20.0f));
            PSMTXConcat(missile->matrix, rot, missile->matrix);
        }
    } else {
        elapsed %= 15;
        if (elapsed == 0) {
            angle = 0.0f;
            if (local.z > angle) {
                angle = -DEG2RAD_F(20.0f);
            }
            if (local.z < 0.0f) {
                angle = DEG2RAD_F(10.0f);
            }
            if (local.x > 100.0f && absf(angle) < 0.0017453292482296542) {
                angle = 2.0 * (3.1415926 * (f32)(HSD_Randi(10) - 5)) / 360.0;
            }
            if (angle != 0.0f) {
                PSMTXRotRad(rot, 'Y', angle);
                PSMTXConcat(missile->matrix, rot, missile->matrix);
            }
        }
        if (elapsed == 10) {
            angle = 0.0f;
            if (local.y > angle) {
                angle = DEG2RAD_F(20.0f);
            }
            if (local.y < 0.0f) {
                angle = -DEG2RAD_F(10.0f);
            }
            if (angle != 0.0f) {
                PSMTXRotRad(rot, 'Z', angle);
                PSMTXConcat(missile->matrix, rot, missile->matrix);
            }
        }
        PSMTXRotRad(rot, 'X', DEG2RAD_F(10.0f));
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    }
}
