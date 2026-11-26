#include "zoid.h"

extern void zdWeaponChg(ZoidState *zoid);
extern void zdWeaponFireON_(ZoidState *zoid, s32 mount);

void zdWeaponFireON(ZoidState *zoid)
{
    WeaponMount *mount;
    ZoidControlData *control;
    s32 selected;
    s32 state;
    s32 index;

    if (zoid != 0 && zoid->joint != 0) {
        selected = zoid->weapon_mount;
        control = zoid->control;
        if (selected == -1) {
            zdWeaponChg(zoid);
            return;
        }
        if (selected != -1 && zoid->selected_weapon_mount != -1 &&
            zoid->selected_weapon_mount == selected) {
            selected = zoid->selected_weapon_mount;
            if (selected != WEAPON_MOUNT_SUPER_ATTACK) {
                mount = &zoid->weapon_mounts[selected];
                if (selected == WEAPON_MOUNT_SUPER_ATTACK) {
                    mount->active = 1;
                }
                if (zoid->selected_weapon_mount != WEAPON_MOUNT_SUPER_ATTACK && mount->active != 0) {
                    state = mount->state;
                    if (state == 2 || state == 3 || state == 5) {
                        if (state != 3) {
                            mount->state = 3;
                        }
                        selected = zoid->selected_weapon_mount;
                        state = control->field_0140[selected];
                        if ((state != 3 && state != 4) || (zoid->jump_phase == 0 &&
                            zoid->action != ZOID_ACTION_STEP_3 && zoid->action != ZOID_ACTION_STEP_2 &&
                            zoid->action != ZOID_ACTION_STEP_0 && zoid->action != ZOID_ACTION_STEP_1)) {
                            if (selected == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
                                for (index = 0; index < 10; index++) {
                                    zdWeaponFireON_(zoid, index);
                                }
                            } else {
                                zdWeaponFireON_(zoid, selected);
                            }
                        }
                    }
                }
            }
        }
    }
}
