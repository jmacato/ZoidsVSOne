#include "missile.h"

extern void sLinier3d(f32 *current, f32 *target, f32 fraction);
extern void sGlobal2Local(HSD_JObj *joint);

void sEffectTrace(Effect *effect)
{
    s32 i;
    s32 n;
    f32 rate;

    if (effect->source == 0)
        return;
    if (effect->joints[0].joint == 0)
        return;
    if (effect->type <= 0)
        return;
    rate = Tea_effectdat[effect->type].trace_rate / 100.0;
    effect->joints[0].position[0] = effect->joints[0].joint->matrix[0][3];
    effect->joints[0].position[1] = effect->joints[0].joint->matrix[1][3];
    effect->joints[0].position[2] = effect->joints[0].joint->matrix[2][3];
    for (i = 17; i > 0; i--) {
        HSD_JObj *previous = effect->joints[i - 1].joint;
        HSD_JObj *joint = effect->joints[i].joint;
        if (previous != 0 && joint != 0) {
            f32 *last = effect->joints[i - 1].position;
            sLinier3d(effect->joints[i].position, last, rate);
        }
    }
    for (i = 1; i < 18; i++) {
        HSD_JObj *previous = effect->joints[i - 1].joint;
        HSD_JObj *joint = effect->joints[i].joint;
        if (previous != 0 && joint != 0) {
            f32 *last = effect->joints[i - 1].position;
            f32 *current = effect->joints[i].position;
            for (n = 0; n < 3; n++) {
                if (last[n] != current[n])
                    break;
            }
            if (n == 3)
                current[0] += 0.01;
            for (n = 0; n < 3; n++) {
                joint->matrix[n][3] = current[n];
            }

            sGlobal2Local(joint);
        }
    }
}
