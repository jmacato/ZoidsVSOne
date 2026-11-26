#include "weapon.h"

extern void sLinier3d(f32 *current, f32 *target, f32 fraction);
extern void sGlobal2Local(HSD_JObj *joint);

void sWeaponTrace(WeaponState *weapon)
{
    s32 index;
    s32 i;
    s32 j;

    if (weapon->trace_joints[0] != 0) {
        for (i = 0; i < 3; i++) {
            (&weapon->trace_positions[0].x)[i] = weapon->trace_joints[0]->matrix[i][3];
        }
        for (index = 12; index > 0; index--) {
            HSD_JObj *joint = weapon->trace_joints[index];

            if (weapon->trace_joints[index - 1] != 0 && joint != 0) {
                Vec3 *previous = &weapon->trace_positions[index - 1];
                Vec3 *point = &weapon->trace_positions[index];

                sLinier3d((f32 *)point, (f32 *)previous, 0.8f);
                for (j = 0; j < 3; j++) {
                    joint->matrix[j][3] = (&point->x)[j];
                }
                sGlobal2Local(joint);
            }
        }
    }
}
