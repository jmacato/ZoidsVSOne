#include "zoid.h"

extern s32 getEndFA(HSD_JObj *joint);
extern void ZoidSetAnimAllPoint(ZoidState *zoid, HSD_JObj *joint, s32 number);
extern void zdWeaponForceFireOnOff_(ZoidState *zoid, s32 mount, s32 on);

void zdOptionUseOnOff2(ZoidState *zoid, s32 on)
{
    WeaponMount *mount;
    s32 state;
    s32 enabled;
    s32 end;
    s32 anim;
    HSD_JObj *joint;
    s32 frame_padding[2];

    mount = &zoid->weapon_mounts[WEAPON_MOUNT_BOOSTER];
    joint = 0;
    state = mount->state;
    enabled = zoid->control->field_0140[WEAPON_MOUNT_BOOSTER];
    if (enabled == 1)
        joint = zoid->animation_exclusion;
    if (joint == 0)
        enabled = 0;
    if (enabled == 1) {
        end = getEndFA(joint);
        anim = -1;
        if (on != 0) {
            switch (state) {
            case 1:
                if (end != 0)
                    anim = 1;
                break;
            case 2:
                if (end != 0)
                    anim = 2;
                break;
            case 3:
                break;
            case 4:
                if (end != 0)
                    anim = 0;
                break;
            default:
                anim = 0;
                break;
            }
        } else {
            switch (state) {
            case 1:
                if (end != 0)
                    anim = 3;
                break;
            case 2:
                anim = 3;
                break;
            case 3:
                anim = 3;
                break;
            case 4:
                if (end != 0)
                    anim = 4;
                break;
            default:
                anim = 4;
                break;
            }
        }
        if (anim != -1) {
            ZoidSetAnimAllPoint(zoid, joint, anim + 159);
            mount->state = anim + 1;
        }
    }
    zoid->booster_on = on;
    zdWeaponForceFireOnOff_(zoid, WEAPON_MOUNT_BOOSTER, on);
}
