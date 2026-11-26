#include "zoid.h"
#include "game_zoid_data.h"

extern void zdEffectMount(ZoidState *zoid, s32 mount, s32 effect);

void zdAtackSetEffect(ZoidState *zoid, s32 attack)
{
    s32 i;
    s32 effect;
    s32 mount;

    for (i = 0; i < 2; i++) {
        effect = Tea_zoiddat[zoid->type].attack_effects[attack][i];
        mount = Tea_zoiddat[zoid->type].attack_effect_mounts[attack][i];
        if (effect > 0 && zoid->weapon_slots[mount].joint != 0) {
            zdEffectMount(zoid, mount, effect);
        }
    }
}
