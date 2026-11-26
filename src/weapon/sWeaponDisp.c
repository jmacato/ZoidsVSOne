#include "weapon.h"

extern void HSD_JObjDispAll(HSD_JObj *joint, void *matrix, u32 passes, u32 flags);

void sWeaponDisp(WeaponState *weapon)
{
    HSD_JObj *joint;

    if (weapon != 0 && (weapon->flags & 1) == 0) {
        joint = weapon->archive->models[weapon->model];
        if (joint != 0) {
            HSD_JObjDispAll(joint, 0, 7, 0);
        }
    }
}
