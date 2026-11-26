#include "zoid.h"
#include "game_zoid_data.h"

extern void zdCalcWeapon(ZoidState *, s32);
extern void zdCalcWeaponS(ZoidState *, s32);
extern void zdCalcMan(ZoidState *, s32);
extern void OSReport(const char *, ...);
void zdCalc(ZoidState *zoid)
{
    ZoidData *data;
    ZoidControlData *control;
    s32 i;
    if (zoid != 0 && zoid->joint != 0) {
        data = &Tea_zoiddat[zoid->type];
        control = zoid->control;
        zoid->radar_range_bonus = 0;
        zoid->search_range_bonus = 0;
        zoid->field_1CB8 = 0;
        zoid->armor_bonus = 0;
        zoid->field_1CC0 = 0;
        zoid->speed_bonus = 0;
        zoid->bullet_power_bonus = 0;
        zoid->melee_power_bonus = 0;
        zoid->turn_bonus = 0;
        for (i = 0; i < 30; i++) {
            if (zoid->weapon_slots[i].joint != 0 && zoid->weapon_slots[i].weapon != -1)
                zdCalcWeapon(zoid, zoid->weapon_slots[i].weapon);
        }
        for (i = 0; i < 3; i++)
            zdCalcWeaponS(zoid, zoid->additional_parts[i]);
        zdCalcMan(zoid, zoid->person);
        zoid->radar_range = data->radar_range + zoid->radar_range_bonus;
        zoid->search_range = data->search_range + zoid->search_range_bonus;
        zoid->armor = data->armor + zoid->armor_bonus;
        zoid->max_speed = control->base_max_speed + zoid->speed_bonus;
        OSReport("add power z%d \222e=%d , \212i\223\254=%d \n", zoid->index, zoid->bullet_power_bonus, zoid->melee_power_bonus);
    }
}
