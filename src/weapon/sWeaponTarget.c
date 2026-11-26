#include "weapon.h"
#include "joint_matrix.h"

#define NULL 0

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !matrix_is_dirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

void sWeaponTarget(WeaponState *weapon, HSD_JObj *target)
{
    HSD_JObj *joint;
    s32 i;
    s32 j;

    if (weapon == 0)
        return;
    if (target == 0)
        return;
    if (weapon->animation >= 4)
        return;
    joint = weapon->target_joint;
    if (joint == 0)
        return;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            joint->matrix[i][j] = target->matrix[i][j];
        }
    }
    sGlobal2Local(joint);
    HSD_JObjSetMtxDirty(joint);
}
