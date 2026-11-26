#include "zoid.h"

typedef struct ZoidInfo {
    s32 type;
    s16 additional_parts[3];
    s16 health_bonus;
    u8 reserved_0C[0xC];
    s16 weapon_slots[10];
    s16 weapon_parts[10];
    u8 reserved_40[0xF];
    s8 color;
    s8 person;
} ZoidInfo;

extern s32 ZoidInit_(ZoidState *zoid, s32 type, s32 flags);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);
extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);

s32 infoLoadZoid0(ZoidState *zoid, ZoidInfo *info)
{
    if (zoid == 0) {
        return 0;
    }
    if (info == 0) {
        return 0;
    }
    ZoidInit_(zoid, info->type, 0);
    zoid->max_health += info->health_bonus;
    zoid->health += info->health_bonus;
    zoid->person = info->person;
    ZoidColor(zoid, info->color, 0);
    return 1;
}

s32 infoLoadZoid1(ZoidState *zoid, ZoidInfo *info)
{
    s32 i;
    s64 frame_padding;

    if (zoid == 0) {
        return 0;
    }
    if (info == 0) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        s32 slot = info->weapon_slots[i];
        s32 part = info->weapon_parts[i];

        if (slot != 27 && slot != -1 && part > 0) {
            sWeaponMount(part, zoid, slot, i);
        }
    }
    zoid->additional_parts[0] = info->additional_parts[0];
    zoid->additional_parts[1] = info->additional_parts[1];
    zoid->additional_parts[2] = info->additional_parts[2];
    return 1;
}

s32 infoLoadZoid(ZoidState *zoid, ZoidInfo *info)
{
    s32 i;
    s64 frame_padding;

    if (zoid == 0) {
        return 0;
    }
    if (info == 0) {
        return 0;
    }
    ZoidInit_(zoid, info->type, 0);
    zoid->max_health += info->health_bonus;
    zoid->health += info->health_bonus;
    zoid->person = info->person;
    ZoidColor(zoid, info->color, 0);
    for (i = 0; i < 10; i++) {
        s32 slot = info->weapon_slots[i];
        s32 part = info->weapon_parts[i];

        if (slot != 27 && slot != -1 && part > 0) {
            sWeaponMount(part, zoid, slot, i);
        }
    }
    zoid->additional_parts[0] = info->additional_parts[0];
    zoid->additional_parts[1] = info->additional_parts[1];
    zoid->additional_parts[2] = info->additional_parts[2];
    return 1;
}
