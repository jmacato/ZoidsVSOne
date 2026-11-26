#include "zoid.h"
#include "game_part_data.h"
#include "game_person_data.h"

void zdCalcWeaponS(ZoidState *zoid, s32 part)
{
    if (part > 0) {
        PartData *data = &Tea_partsdat[part];
        zoid->radar_range_bonus += data->radar_range_bonus;
        zoid->search_range_bonus += data->search_range_bonus;
        zoid->armor_bonus += data->armor_bonus;
        zoid->field_1CC0 += data->field_E4;
        zoid->speed_bonus += data->speed_bonus;
        zoid->turn_bonus += data->turn_bonus;
        if (data->category == 3) {
            zoid->bullet_power_bonus += data->power;
            zoid->melee_power_bonus += data->power;
        }
    }
}

void zdCalcMan(ZoidState *zoid, s32 person)
{
    if (zoid != 0 && zoid->joint != 0) {
        PersonData *pilot = &Tea_persondat[person];
        zoid->turn_bonus += pilot->turn_bonus;
        zoid->melee_power_bonus += pilot->melee_power_bonus;
        zoid->bullet_power_bonus += pilot->bullet_power_bonus;
    }
}
