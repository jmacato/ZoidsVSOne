#include "weapon.h"
#include "game_part_data.h"
extern struct HSD_Fog *fogG;
extern void HSD_FogSet(struct HSD_Fog *fog);
extern void sWeaponDisp(WeaponState *weapon);

void sWeaponDispAll(void)
{
    WeaponState *weapon;
    s32 index;
    s32 use_fog;

    for (index = 0; index < 100; index++) {
        weapon = &sWeapon[index];
        {
            s32 is_active = weapon->active != 0;
            if (is_active) {
                if ((Tea_partsdat[weapon->type].flags & PART_FLAG_NO_FOG) != 0) {
                    use_fog = 0;
                } else {
                    use_fog = 1;
                }
                {
                    s32 has_fog = fogG != 0;
                    if (has_fog)
                        HSD_FogSet(use_fog != 0 ? fogG : 0);
                }
                sWeaponDisp(weapon);
            }
        }
    }
    if (fogG != 0) {
        HSD_FogSet(fogG);
    }
}
