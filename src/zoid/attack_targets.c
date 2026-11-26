#include "zoid.h"
#include "game_zoid_data.h"

extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void zdAtk(ZoidState *zoid)
{
    ZoidState *target;
    s32 attack;
    s32 index;
    f32 range;
    f32 half_angle;
    f64 full_angle;
    f32 angle;

    if (zoid != 0 && zoid->joint != 0) {
        attack = 0;
        if (zoid->action == ZOID_ACTION_ATTACK_0) attack = 0;
        if (zoid->action == ZOID_ACTION_ATTACK_1) attack = 1;
        if (zoid->action == ZOID_ACTION_ATTACK_2) attack = 2;
        if (zoid->action == ZOID_ACTION_ATTACK_3) attack = 3;
        if (zoid->action == ZOID_ACTION_ATTACK_4) attack = 4;
        if (zoid->action == ZOID_ACTION_ATTACK_5) attack = 5;
        if (zoid->action == ZOID_ACTION_ATTACK_6) attack = 6;
        if (zoid->action == ZOID_ACTION_ATTACK_7) attack = 7;
        if (zoid->action == ZOID_ACTION_ATTACK_8) attack = 8;
        if (zoid->action == ZOID_ACTION_ATTACK_9) attack = 9;
        range = Tea_zoiddat[zoid->type].attack_ranges[attack];
        full_angle = 2.0 * (3.1415926 * Tea_zoiddat[zoid->type].attack_angles[attack]) / 360.0;
        half_angle = full_angle / 2.0;
        for (index = 0; index < 16; index++) {
            target = &Zoid[index];
            zoid->attack_in_range[index] = 0;
            if (target->joint != 0 && target->death_started == 0 &&
                (u32)target->slot != (u32)zoid->slot && !(range < zoid->distances[index])) {
                angle = ZoidCalcAngle(zoid, (Vec3 *)target->position);
                if (angle != 100.0f) {
                    if (!(absf(angle) > half_angle))
                        zoid->attack_in_range[index] = 1;
                }
            }
        }
    }
}
