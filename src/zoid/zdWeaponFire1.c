#include "zoid.h"

extern void zdWeaponFire1_(ZoidState *zoid, s32 mount);

void zdWeaponFire1(ZoidState *zoid)
{
    WeaponMount *mount;
    ZoidControlData *control;
    s32 selected;
    s32 state;
    s32 index;

    if (zoid != 0 && zoid->joint != 0) {
        selected = zoid->weapon_mount;
        control = zoid->control;
        if (selected != -1 && zoid->selected_weapon_mount != -1 &&
            zoid->selected_weapon_mount == selected) {
            mount = &zoid->weapon_mounts[selected];
            if (mount->active != 0) {
                state = mount->state;
                if (state == 2 || state == 3 || state == 5) {
                    if (state != 5) {
                        mount->state = 5;
                    }
                    state = control->field_0140[zoid->weapon_mount];
                    if ((state != 3 && state != 4) || (zoid->jump_phase == 0 &&
                        zoid->action != ZOID_ACTION_STEP_3 && zoid->action != ZOID_ACTION_STEP_2 &&
                        zoid->action != ZOID_ACTION_STEP_0 && zoid->action != ZOID_ACTION_STEP_1)) {
                        zoid->anim1_frames = 0;
                        if (zoid->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
                            for (index = 0; index < 10; index++) {
                                zdWeaponFire1_(zoid, index);
                            }
                        } else {
                            zdWeaponFire1_(zoid, zoid->weapon_mount);
                        }
                    }
                }
            }
        }
    }
}
