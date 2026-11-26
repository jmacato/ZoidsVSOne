#include "weapon.h"

extern void stSetFlag(HSD_JObj *joint, JointPose *pose, f32 opacity);

void sWeaponSetPer00(s32 index, f32 opacity)
{
    WeaponState *weapon;

    if (index >= 0 && index < 100) {
        weapon = &sWeapon[index];
        if (weapon->active != 0) {
            stSetFlag(weapon->archive->models[weapon->model], weapon->pose, opacity);
        }
    }
}
