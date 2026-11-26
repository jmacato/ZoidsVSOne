#include "missile.h"

#define NULL 0

extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern void sGlobal2Local(HSD_JObj *joint);

void msFlyTrace(Missile *missile)
{
    f32 rate;
    s32 i;
    s32 k;
    s32 j;
    f32 pad_stack[2];

    if (missile == NULL)
        return;
    if (missile->purge_timer != 0)
        return;
    if (missile->beam_joints[0] == NULL)
        return;
    rate = Tea_bulletdat[missile->bullet].trace_rate * 0.01;
    for (i = 6; i > 0; i--) {
        if (missile->beam_joints[i] != NULL && missile->beam_joints[i - 1] != NULL) {
            for (k = 0; k < 3; k++) {
                missile->beam_positions[i][k] = sLiner(missile->beam_positions[i - 1][k], missile->beam_positions[i][k], rate);
                missile->beam_joints[i]->matrix[k][3] = missile->beam_positions[i][k];
            }
            for (k = 0; k < 3; k++) {
                for (j = 0; j < 3; j++)
                    missile->beam_joints[i]->matrix[k][j] = missile->beam_joints[i - 1]->matrix[k][j];
            }
            sGlobal2Local(missile->beam_joints[i]);
        }
    }
}
