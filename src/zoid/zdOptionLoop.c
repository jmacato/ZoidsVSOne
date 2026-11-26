#include "zoid.h"

extern void zdOptionUseOK(ZoidState *zoid);
extern void zdOptionUse(ZoidState *zoid);
extern void zdOptionUseOnOff(ZoidState *zoid, s32 on);

#define OPTION_ON(zoid) (*(s8 *)&(zoid)->option_use_state)
#define OPTION_PREV(zoid) (*(s8 *)&(zoid)->option_use_previous)

void zdOptionLoop(ZoidState *zoid)
{
    s32 add;

    zoid->option_active = 0;
    if (zoid->option_energy_max == 0)
        return;
    if (zoid->super_attack_input != 0)
        OPTION_ON(zoid) = 0;
    if (zoid->option_energy < 0)
        zoid->option_energy = 0;
    zdOptionUseOK(zoid);
    if (OPTION_ON(zoid) != 0) {
        if (zoid->option_energy == 0)
            OPTION_ON(zoid) = 0;
        if (OPTION_PREV(zoid) == 0 && zoid->option_energy_max != zoid->option_energy)
            OPTION_ON(zoid) = 0;
    }
    if (OPTION_ON(zoid) != 0) {
        if (OPTION_PREV(zoid) != 0)
            zoid->option_energy -= zoid->option_hold_cost;
        else
            zoid->option_energy -= zoid->option_start_cost;
        zdOptionUse(zoid);
    } else {
        add = zoid->option_recharge;
        if (zoid->damages[1].maximum_health != 0 && zoid->damages[1].health == 0)
            add /= 2;
        if (add == 0 && zoid->option_recharge != 0)
            add = 1;
        zoid->option_energy += add;
        if (zoid->option_energy >= zoid->option_energy_max)
            zoid->option_energy = zoid->option_energy_max;
    }
    zdOptionUseOnOff(zoid, OPTION_ON(zoid));
    OPTION_PREV(zoid) = OPTION_ON(zoid);
}
