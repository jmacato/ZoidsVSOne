#include "zoid.h"
#include "missile.h"

void zdEffectMount(ZoidState *zoid, s32 mount, s32 effect)
{
    HSD_JObj *joint;
    s32 mode;

    if (effect <= 0)
        return;
    if (zoid == 0)
        return;
    if ((joint = zoid->joint) == 0)
        return;
    if (mount >= 27)
        return;
    if (mount < 0)
        return;
    if (effect >= 110)
        return;
    mode = 2;
    if (Tea_effectdat[effect].kind == EFFECT_KIND_ZOID) {
        mode = 3;
    } else {
        joint = zoid->weapon_slots[mount].joint;
        if (joint == 0)
            return;
    }
    sEffectSet(effect, mode, 0, joint, zoid);
}
