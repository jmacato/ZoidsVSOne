#include "zoid_ai.h"
#include "os_time.h"
#include "game_part_data.h"
#include "missile.h"

extern void OSReport(const char *format, ...);
extern void ZeroMemory(void *address, u32 size);
extern void *memcpy(void *dst, const void *src, u32 size);
extern void TEA_SetTimerInit(void);
extern u32 TEA_AfterTimemSec(void);
extern u32 __OSBusClock : 0x800000F8;
extern u32 vsyncN;

#define AI_RAND() (((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 20)

static inline s32 aiWeaponBullet(s32 index)
{
    s32 id;
    s32 bullet;
    id = zdAI_WeaponGetID(index);
    bullet = Tea_partsdat[id].bullets[0];
    return bullet;
}

#define BULLET_KIND(index) (Tea_bulletdat[aiWeaponBullet(index)].kind)
#define TARGET_DIST(zoid) ((zoid)->distances[(zoid)->target_slot])

#pragma readonly_strings on

AiCommand aiCom0[56] = {
    {0, {0, 0, 0}, AI_CMD_FIRE_OFF, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_INIT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SEARCH_ENEMY, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 100.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 50.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_OUT, 100.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_OUT, 200.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 90.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 270.0f, 120},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 2},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 60},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 3},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_OUT, 100.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_OUT, 200.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 90.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 270.0f, 120},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 4},
    {0, {0, 0, 0}, AI_CMD_NEXT_WEAPON, 0.0f, 0},
    {AI_LABEL_GOTO, {0, 0, 0}, 3, 0.0f, 0},
};

AiCommand aiCom1[54] = {
    {0, {0, 0, 0}, AI_CMD_FIRE_OFF, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_INIT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_MISSILE_DISTANCE, 60.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SEARCH_ENEMY, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 15.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 300},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 2},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 15.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 300},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 90.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 270.0f, 120},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 15.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 300},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 90.0f, 120},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 270.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_NEXT_WEAPON, 0.0f, 0},
    {AI_LABEL_GOTO, {0, 0, 0}, 3, 0.0f, 0},
};

AiCommand aiCom2[64] = {
    {0, {0, 0, 0}, AI_CMD_FIRE_OFF, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_INIT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 4},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 80.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_98, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 300},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 100.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 120},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_IN, 60.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN_OUT, 200.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_NEXT_WEAPON, 0.0f, 0},
    {AI_LABEL_GOTO, {0, 0, 0}, 2, 0.0f, 0},
};

AiCommand aiCom3[87] = {
    {0, {0, 0, 0}, AI_CMD_FIRE_OFF, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_INIT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_MISSILE_DISTANCE, 60.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SEARCH_ENEMY, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_98, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_SET_LEN, 20.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 300},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, -10.0f, 180},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_98, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 180},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_98, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN, 20.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 90.0f, 120},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 2},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 270.0f, 120},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_FACED_ACTION, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_98, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 120},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 180.0f, 180},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 90},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 60},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_LEN, 20.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_98, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_SPD, 10.0f, 150},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 90.0f, 120},
    {0, {0, 0, 0}, AI_CMD_MELEE, 0.0f, 60},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_98, 0.0f, 1},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE_ON, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_SET_ANGLE_ON, 270.0f, 120},
    {0, {0, 0, 0}, AI_CMD_LOOK, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_FIRE1, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_TARGET_NEXT, 0.0f, 0},
    {0, {0, 0, 0}, AI_CMD_NEXT_WEAPON, 0.0f, 0},
    {AI_LABEL_GOTO, {0, 0, 0}, 3, 0.0f, 0},
};

AiData aiDat[16];
AiCommand aiCom;

void aiPrologue(s32 index)
{
    OSReport("AI Start \n");
    ZeroMemory(&aiDat[index], sizeof(AiData));
    aiDat[index].script = 0;
    aiDat[index].field_28 = 0;
    aiDat[index].field_2C = 0;
    aiDat[index].command_timer = 0;
    aiDat[index].missile_range = 20;
    aiDat[index].melee_range = 30;
    aiDat[index].terrain_distance = 25;
    aiDat[index].missile_step_angle = 90;
    aiDat[index].ground_rise = 0;
    aiDat[index].side = 1;
    aiDat[index].near_action = 1;
    aiDat[index].faced_action = 7;
    aiDat[index].attacked_action = 2;
    aiDat[index].field_4C = 1;
    aiDat[index].melee_burst = 30;
    aiDat[index].melee_cooldown_time = 120;
    aiDat[index].target_ahead = 0;
    aiDat[index].target_facing_me = 0;
    aiDat[index].obstacle_ahead = 0;
    aiDat[index].avoiding_obstacle = 0;
    aiDat[index].under_attack = 0;
    aiDat[index].field_68 = 0;
    aiDat[index].stopped_timer = 90;
    aiDat[index].fire_timer = 60;
    aiDat[index].weapon_timer = 180;
    aiDat[index].step_timer = 110;
    aiDat[index].step_interval = 300;
    aiDat[index].melee_left = 30;
    aiDat[index].melee_cooldown = 120;
    aiDat[index].field_78 = 120;
    aiDat[index].len_in_timer = -1;
    aiDat[index].weapon_ready = 1;
    aiDat[index].enemy_found = 0;
    aiDat[index].field_88 = 0;
    aiDat[index].field_8C = 0;
    aiDat[index].field_90 = 0;
    aiDat[index].rapid_fire = 0;
    aiDat[index].field_98 = 1;
    aiDat[index].command_index = 0;
    TEA_SetTimerInit();
    if (index >= 0 && index < 16) {
        ZoidState *zoid = &Zoid[index];
        /* etc/n_Zoid.dat types: 15 Gojulas, 4 Molga, 21 Death Saurer, 22 Death Stinger */
        if (zoid->type == 15) {
            aiDat[index].script = 1;
            aiDat[index].command_index = 0;
            aiDat[index].command_timer = 0;
            if (aiDat[index].script == 1)
                memcpy(&aiCom, &aiCom1[aiDat[index].command_index], sizeof(AiCommand));
            OSReport("AI Set \203S\203W\203\205\203\211\203X---------------\n");
        } else if (zoid->type == 4) {
            aiDat[index].script = 2;
            aiDat[index].command_index = 0;
            aiDat[index].command_timer = 0;
            if (aiDat[index].script == 2)
                memcpy(&aiCom, &aiCom2[aiDat[index].command_index], sizeof(AiCommand));
            OSReport("AI Set \203\202\203\213\203K-------------------\n");
        } else if (zoid->type == 21 || zoid->type == 22) {
            aiDat[index].script = 3;
            aiDat[index].command_index = 0;
            aiDat[index].command_timer = 0;
            if (aiDat[index].script == 3)
                memcpy(&aiCom, &aiCom3[aiDat[index].command_index], sizeof(AiCommand));
            OSReport("AI Set \203f\203X\203X\203e\203B\203\223\203K-------------------\n");
        } else {
            OSReport("AI Set Def-------------------\n");
            aiDat[index].script = 0;
            aiDat[index].command_index = 0;
            aiDat[index].command_timer = 0;
            memcpy(&aiCom, &aiCom0[aiDat[index].command_index], sizeof(AiCommand));
        }
    }
}

void aiEpilogue(s32 index)
{
    ZeroMemory(&aiDat[index], sizeof(AiData));
}

#pragma force_active on
static const char sLabelKeepAngle[] = "\212p\223x\210\333\216\235";
/* unreferenced labels: "none", "inside radius", "outside radius", sLabelKeepAngle, "circle", "" */
static const u32 sRadiusAngleLabels[6] = {0x802A0BC0, 0x802A0BC8, 0x802A0BD0, 0x800F1F00, 0x802A0BD8, 0x802A0BE0};
static const char sLabelSearchEnemy[] = "\223G\202\360\222T\202\267";
static const char sLabelTargetSet[] = "targetSet";
static const char sLabelWeaponChange[] = "\225\220\212\355\225\317\215X";
static const char sLabelMeleeAttack[] = "\212i\223\254\215U\214\202";
/* unreferenced labels: "none", sLabelSearchEnemy, sLabelTargetSet, "Next enemy", sLabelWeaponChange, "fire 1", sLabelMeleeAttack, "" */
static const u32 sActionLabels[8] = {0x802A0BC0, 0x800F1F24, 0x800F1F30, 0x802A0BE4, 0x800F1F3C, 0x802A0BEC, 0x800F1F48, 0x802A0BE0};
#pragma force_active off

void ai(s32 index)
{
    char *unused[6];
    ZoidState *zoid;
    ZoidAIState *zoid_ai;
    s32 ang;
    s32 next;
    s32 bullet;

    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != 0) {
            zoid_ai = zoid->ai;

            if (aiDat[index].script == 0)
                memcpy(&aiCom, &aiCom0[aiDat[index].command_index], sizeof(AiCommand));
            if (aiDat[index].script == 1)
                memcpy(&aiCom, &aiCom1[aiDat[index].command_index], sizeof(AiCommand));
            if (aiDat[index].script == 2)
                memcpy(&aiCom, &aiCom2[aiDat[index].command_index], sizeof(AiCommand));
            if (aiDat[index].script == 3)
                memcpy(&aiCom, &aiCom3[aiDat[index].command_index], sizeof(AiCommand));

            if (vsyncN % 10 == 0) {
                aiDat[index].missile_distance = zdAI_ComeMissile(index);
                if (aiDat[index].missile_distance != -1)
                    aiDat[index].field_36 = zdAI_AngZoidME(index);
            }

            ang = zdAI_AngZoidME(index);
            aiDat[index].angle_to_target = ang;
            if (ang > -30 && ang < 30)
                aiDat[index].target_ahead = 1;
            else
                aiDat[index].target_ahead = 0;

            if (vsyncN % 10 == 1) {
                aiDat[index].ground_rise = zdAI_goY(index, 0, aiDat[index].terrain_distance);
                if (aiDat[index].ground_rise > 20)
                    aiDat[index].obstacle_ahead = 1;
                else
                    aiDat[index].obstacle_ahead = 0;
                if (zdAI_goWall(index, (f32)aiDat[index].terrain_distance) == 1) {
                    aiDat[index].obstacle_ahead = 1;
                    aiDat[index].target_ahead = 0;
                }
            }

            ang = zdAI_AngZoidEM(index);
            if (ang > -30 && ang < 30)
                aiDat[index].target_facing_me = 1;
            else
                aiDat[index].target_facing_me = 0;

            if (zdAI_IsAtackMine(index) == 1)
                aiDat[index].under_attack = 1;
            else
                aiDat[index].under_attack = 0;

            if (zoid->health == 0)
                return;

            if (aiDat[index].command_timer > 0)
                aiDat[index].command_timer--;
            if (aiDat[index].command_timer == 0)
                next = 1;
            else
                next = 0;
            if (aiDat[index].command_timer < -1)
                aiDat[index].command_timer = 0;

            if (next == 1) {
                if (aiCom.label == AI_LABEL_SCRIPT) {
                    aiDat[index].script = aiCom.command;
                    aiDat[index].command_index = 0;
                    aiDat[index].command_timer = 0;
                    aiDat[index].field_2C = 0;
                    return;
                }
                if (aiCom.label == AI_LABEL_GOTO) {
                    aiDat[index].command_index = aiCom.command;
                    aiCom.command = 0;
                    aiDat[index].command_timer = aiCom.duration;
                    aiDat[index].field_2C = 0;
                    return;
                }
                aiDat[index].command_index++;
                aiDat[index].command_timer = aiCom.duration;
                aiDat[index].field_2C = 0;
            }

            if (next == 1 && aiDat[index].field_2C == 0) {
                switch (aiCom.command) {
                case AI_CMD_SEARCH_ENEMY:
                    if (zdAI_SearchEnemy(index) == -1) {
                        zdAI_SetZoid0(index, zoid->target_slot);
                        aiDat[index].enemy_found = 0;
                    } else {
                        zdAI_SetLockZoid(index);
                        aiDat[index].enemy_found = 1;
                    }
                    break;
                case AI_CMD_FIRE1:
                    aiDat[index].field_90 = 0;
                    if (aiDat[index].target_ahead == 1) {
                        aiDat[index].fire_timer = 120;
                        if (zdAI_IsTarget(index)) {
                            aiDat[index].fire_timer = 30;
                            zdAI_WeaponFire1(index);
                            if (BULLET_KIND(index) == BULLET_KIND_STRAIGHT)
                                zdAI_WeaponFireON(index);
                            OSReport("AI[%d]%d:%d \210\352\224\255\224\255\216\313: \n", aiDat[index].script, index, zoid->type);
                        } else if (index == 2) {
                            if (zdAI_SearchEnemy(index) == -1) {
                                OSReport("AI[%d]%d:%d \226\332\225W0\202\326: \n", aiDat[index].script, index, zoid->type);
                                zdAI_SetZoid0(index, 0);
                                zdAI_SetLenIn(index, 100.0f);
                                zdAI_SetAngleSpd(index, 10);
                                zdAI_SetAngleON(index, 90);
                                zdAI_TargetSet2(index);
                                zdAI_WeaponFireOFF(index);
                            } else {
                                zdAI_SetLockZoid(index);
                            }
                        } else {
                            aiNextWeapon(index);
                            if (zdAI_SearchEnemy(index) == -1)
                                zdAI_TargetNext(index);
                            else
                                zdAI_SetLockZoid(index);
                            if (AI_RAND() == 0) {
                                zdAI_SetLenIn(index, 50.0f);
                                zdAI_SetAngleON(index, 180);
                            } else if (AI_RAND() == 1) {
                                zdAI_SetLenOut(index, 100.0f);
                                zdAI_SetAngleON(index, 180);
                            }
                        }
                    } else if (aiDat[index].target_facing_me == 0) {
                        aiDat[index].fire_timer = 120;
                        if (zdAI_IsTarget(index)) {
                            if (zdAI_Look(index)) {
                                zdAI_WeaponFire1(index);
                            } else if (BULLET_KIND(index) == BULLET_KIND_AT20) {
                                zdAI_WeaponFireON(index);
                                zdAI_WeaponFire1(index);
                            }
                        } else if (index == 2) {
                            if (zdAI_SearchEnemy(index) == -1) {
                                zdAI_SetZoid0(index, 0);
                                zdAI_SetLenIn(index, 100.0f);
                                zdAI_SetAngleSpd(index, 10);
                                zdAI_SetAngleON(index, 90);
                                zdAI_TargetSet2(index);
                                zdAI_WeaponFireOFF(index);
                            } else {
                                zdAI_SetLockZoid(index);
                            }
                        } else {
                            if (zdAI_SearchEnemy(index) == -1)
                                zdAI_TargetNext(index);
                            else
                                zdAI_SetLockZoid(index);
                            if (AI_RAND() == 0) {
                                zdAI_SetLenIn(index, 50.0f);
                                zdAI_SetAngleON(index, 180);
                            } else if (AI_RAND() == 1) {
                                zdAI_SetLenOut(index, 100.0f);
                                zdAI_SetAngleON(index, 180);
                            }
                        }
                    } else {
                        if (zdAI_IsTarget(index) && BULLET_KIND(index) == BULLET_KIND_AT20)
                            zdAI_WeaponFire1(index);
                    }
                    break;
                case AI_CMD_FIRE_ON:
                    zdAI_WeaponFireON(index);
                    aiDat[index].rapid_fire = 1;
                    break;
                case AI_CMD_FIRE_OFF:
                    zdAI_WeaponFireOFF(index);
                    aiDat[index].rapid_fire = 0;
                    OSReport("AI[%d]%d:%d \230A\216\313\202\342\202\337\202\351\n", aiDat[index].script, index, zoid->type);
                    break;
                case AI_CMD_MELEE:
                    OSReport("AI[%d]%d:%d \212i\223\254\n", aiDat[index].script, index, zoid->type);
                    if (zdAI_IsAtack(index) == 1) {
                        zdAI_Atack1(index);
                        aiDat[index].field_88 = 0;
                        zdAI_SetLen(index, aiDat[index].field_34);
                    } else {
                        aiDat[index].field_88 = 1;
                        zdAI_SetLenIn(index, 15.0f);
                        aiDat[index].field_34 = aiDat[index].melee_range;
                        aiDat[index].command_timer = aiCom.duration;
                        if (aiDat[index].target_ahead == 1) {
                            if (zdAI_IsTarget(index)) {
                                zdAI_WeaponFire1(index);
                            } else if (index == 2) {
                                if (zdAI_SearchEnemy(index) == -1) {
                                    zdAI_SetZoid0(index, 0);
                                    zdAI_SetLenIn(index, 100.0f);
                                    zdAI_SetAngleSpd(index, 10);
                                    zdAI_SetAngleON(index, 90);
                                    zdAI_TargetSet2(index);
                                }
                            } else {
                                if (AI_RAND() == 0) {
                                    zdAI_SetLenIn(index, 50.0f);
                                    zdAI_SetAngleON(index, 180);
                                } else if (AI_RAND() == 1) {
                                    zdAI_SetLenOut(index, 100.0f);
                                    zdAI_SetAngleON(index, 180);
                                }
                            }
                        }
                    }
                    break;
                case AI_CMD_JUMP:
                    zdAI_Jump(index);
                    break;
                case AI_CMD_STEP:
                    zdAI_Step(index, aiCom.value);
                    break;
                case AI_CMD_RUN:
                    zdAI_Run(index, aiCom.value);
                    break;
                case AI_CMD_SET_LEN:
                    zdAI_SetLen(index, aiCom.value);
                    break;
                case AI_CMD_SET_LEN_IN:
                    zdAI_SetLenIn(index, aiCom.value);
                    break;
                case AI_CMD_SET_LEN_OUT:
                    zdAI_SetLenOut(index, aiCom.value);
                    break;
                case AI_CMD_SET_ANGLE_SPD:
                    zdAI_SetAngleSpd(index, (s32)aiCom.value + TEA_AfterTimemSec() % 30);
                    aiDat[index].angle_command = aiCom.command;
                    aiDat[index].angle_value = aiCom.value;
                    break;
                case AI_CMD_SET_ANGLE_ON:
                    zdAI_SetAngleON(index, (s32)aiCom.value + TEA_AfterTimemSec() % 30);
                    aiDat[index].angle_command = aiCom.command;
                    aiDat[index].angle_value = aiCom.value;
                    break;
                case AI_CMD_LOOK:
                    if (zdAI_IsTarget(index))
                        zdAI_Look(index);
                    aiDat[index].field_2C = 1;
                    aiDat[index].command_timer = 120;
                    break;
                case AI_CMD_TARGET_NEXT:
                    zdAI_TargetNext(index);
                    break;
                case AI_CMD_NEXT_WEAPON:
                    OSReport("AI[%d]%d:%d \225\220\212\355\225\317\215X: \n", aiDat[index].script, index, zoid->type);
                    if (aiNextWeapon(index) != 1) {
                        OSReport("\225\317\215X\225s\211\302\n");
                        aiDat[index].weapon_ready = 0;
                        aiDat[index].field_88 = 1;
                        zdAI_SetLenIn(index, aiDat[index].melee_range);
                        aiDat[index].field_34 = aiDat[index].melee_range;
                        aiDat[index].command_timer = 120;
                    }
                    break;
                case AI_CMD_SET_MISSILE_DISTANCE:
                    aiDat[index].missile_distance = aiCom.value;
                    break;
                case AI_CMD_INIT:
                    aiDat[index].missile_range = 20;
                    aiDat[index].melee_range = 30;
                    aiDat[index].terrain_distance = 25;
                    aiDat[index].missile_step_angle = 90;
                    aiDat[index].ground_rise = 0;
                    aiDat[index].side = 1;
                    aiDat[index].near_action = 1;
                    aiDat[index].faced_action = 7;
                    aiDat[index].avoiding_obstacle = 0;
                    aiDat[index].field_4C = 1;
                    aiDat[index].melee_burst = 30;
                    aiDat[index].step_interval = 300;
                    aiDat[index].melee_cooldown_time = 120;
                    aiDat[index].len_in_timer = -1;
                    zdAI_SetZoid0(index, 0);
                    zdAI_SetLenIn(index, 100.0f);
                    zdAI_SetAngleSpd(index, 10);
                    zdAI_SetAngleON(index, 90);
                    zdAI_TargetSet2(index);
                    zdAI_WeaponFireOFF(index);
                    zdAI_Run(index, 0);
                    OSReport("AI[%d]%d:%d \217\211\212\372\211\273 \222n\214`\213\227\227\243=%d\n", aiDat[index].script, index, zoid->type, aiDat[index].terrain_distance);
                    break;
                case AI_CMD_SET_MISSILE_STEP_ANGLE:
                    aiDat[index].missile_step_angle = aiCom.value;
                    break;
                case AI_CMD_SET_NEAR_ACTION:
                    aiDat[index].near_action = aiCom.value;
                    break;
                case AI_CMD_SET_FACED_ACTION:
                    aiDat[index].faced_action = aiCom.value;
                    break;
                case AI_CMD_SET_ATTACKED_ACTION:
                    aiDat[index].attacked_action = aiCom.value;
                    break;
                case AI_CMD_SET_4C:
                    if (aiCom.value == 0.0f)
                        aiDat[index].field_4C = 1;
                    else
                        aiDat[index].field_4C = 0;
                case AI_CMD_SET_STEP_INTERVAL:
                    aiDat[index].step_interval = aiCom.value;
                    break;
                case AI_CMD_SET_98:
                    aiDat[index].field_98 = aiCom.value;
                    break;
                }
            } else {
                if (aiDat[index].field_28 == 1)
                    aiDat[index].field_28 = 0;
                switch (aiCom.command) {
                case AI_CMD_FIRE1:
                    aiDat[index].field_90 = 0;
                    /* missile_hit from sMissileZoid1: 1 hit another slot, 3 hit the same slot */
                    if (zoid_ai->missile_hit == 1) {
                        zdAI_WeaponFireON(index);
                        OSReport("AI[%d]%d:%d \230A\216\313\n", aiDat[index].script, index, zoid->type);
                        aiDat[index].field_2C = 0;
                    }
                    if (zoid_ai->missile_hit == 2 || zoid_ai->missile_hit == 3) {
                        aiDat[index].field_2C = 0;
                        aiNextWeapon(index);
                    }
                    break;
                case AI_CMD_MELEE:
                    if (TARGET_DIST(zoid) <= aiDat[index].melee_range && zdAI_IsTarget(index) && zdAI_Look(index) == 1) {
                        aiDat[index].command_timer = 0;
                        zdAI_Atack1(index);
                        zdAI_SetLen(index, aiDat[index].field_34);
                    }
                    break;
                case AI_CMD_LOOK:
                    if (aiDat[index].target_ahead == 1)
                        aiDat[index].field_2C = 0;
                    aiDat[index].field_2C = 0;
                    break;
                case AI_CMD_NONE:
                    break;
                case 17:
                    break;
                }
            }

            if (aiDat[index].weapon_timer > 0)
                aiDat[index].weapon_timer--;
            if (aiDat[index].fire_timer > 0)
                aiDat[index].fire_timer--;
            if (aiDat[index].fire_timer == 0) {
                zdAI_WeaponFireOFF(index);
                aiDat[index].fire_timer = -1;
                if (aiDat[index].field_4C == 1) {
                    if (zdAI_IsTarget(index)) {
                        zdAI_WeaponFire1(index);
                    } else if (index == 2) {
                        if (zdAI_SearchEnemy(index) == -1) {
                            zdAI_SetZoid0(index, 0);
                            zdAI_SetLenIn(index, 100.0f);
                            zdAI_SetAngleSpd(index, 10);
                            zdAI_SetAngleON(index, 90);
                            zdAI_TargetSet2(index);
                        } else {
                            zdAI_SetZoid(index);
                        }
                    } else {
                        if (zdAI_SearchEnemy(index) == -1)
                            zdAI_TargetNext(index);
                        else
                            zdAI_SetZoid(index);
                        if (AI_RAND() == 0) {
                            zdAI_SetLenIn(index, 50.0f);
                            zdAI_SetAngleON(index, 180);
                        } else if (AI_RAND() == 1) {
                            zdAI_SetLenOut(index, 100.0f);
                            zdAI_SetAngleON(index, 180);
                        }
                    }
                }
                aiNextWeapon(index);
            }

            if (aiDat[index].len_out_timer > 0)
                aiDat[index].len_out_timer--;
            if (aiDat[index].melee_cooldown > 0)
                aiDat[index].melee_cooldown--;

            if (aiDat[index].missile_distance != -1 && aiDat[index].missile_distance <= aiDat[index].missile_range) {
                if (aiDat[index].field_4C == 1)
                    aiDat[index].fire_timer = 0;
                if (aiDat[index].step_timer <= 0) {
                    aiDat[index].step_timer = aiDat[index].step_interval;
                    if (aiDat[index].missile_step_angle > 0)
                        zdAI_Step(index, (aiDat[index].field_36 + aiDat[index].missile_step_angle) % 360);
                    if (aiDat[index].missile_step_angle == -1)
                        zdAI_Jump(index);
                } else {
                    aiDat[index].step_timer--;
                    if (aiDat[index].target_facing_me == 1) {
                        aiDat[index].command_timer = 180;
                        zdAI_SetLenIn(index, 5.0f);
                        if (TARGET_DIST(zoid) <= aiDat[index].melee_range && zdAI_IsAtack(index) == 1 && aiDat[index].melee_cooldown <= 0)
                            zdAI_Atack1(index);
                    } else if (aiDat[index].command_timer <= 0) {
                        aiDat[index].len_out_timer = 300;
                        aiDat[index].command_timer = 180;
                        zdAI_SetLenOut(index, 300.0f);
                        zdAI_SetAngleSpd(index, (vsyncN % 3 - 1) * 10);
                        if (zdAI_IsTarget(index)) {
                            aiDat[index].fire_timer = 120;
                            zdAI_WeaponFire1(index);
                        }
                        aiDat[index].len_in_timer = 240;
                    }
                }
            }

            if (aiDat[index].under_attack == 1) {
                if (aiDat[index].attacked_action == 1)
                    zdAI_Jump(index);
                if (aiDat[index].attacked_action == 2) {
                    if (aiDat[index].angle_to_target >= 0) {
                        if (aiDat[index].side == 1)
                            zdAI_Step(index, aiDat[index].angle_to_target + 90);
                        else
                            zdAI_Step(index, (aiDat[index].angle_to_target + 270) % 360);
                    } else {
                        if (aiDat[index].side == 1)
                            zdAI_Step(index, (aiDat[index].angle_to_target + 630) % 360);
                        else
                            zdAI_Step(index, (aiDat[index].angle_to_target + 450) % 360);
                    }
                }
                if (aiDat[index].field_4C == 1)
                    aiDat[index].fire_timer = 30;
            }

            if (aiDat[index].avoiding_obstacle == 1) {
                if (aiDat[index].obstacle_ahead == 0) {
                    aiDat[index].avoiding_obstacle = 0;
                    zdAI_Run(index, 0);
                    aiDat[index].command_timer = 60;
                    if (aiDat[index].angle_command == AI_CMD_SET_ANGLE_SPD) {
                        zdAI_SetAngleSpd(index, 10);
                        zdAI_SetLen(index, aiDat[index].field_34);
                    } else {
                        zdAI_SetAngleON(index, aiDat[index].angle_value);
                    }
                }
            } else if (aiDat[index].obstacle_ahead == 1) {
                if (aiDat[index].side == 1)
                    zdAI_Run(index, 60);
                else
                    zdAI_Run(index, 300);
                OSReport("AI[%d]%d:%d \217\341\212Q\225\250\224\360\202\257\202\351%d\n", aiDat[index].script, index, zoid->type, aiDat[index].side);
                aiDat[index].avoiding_obstacle = 1;
            }

            if (aiDat[index].target_ahead == 1 && TARGET_DIST(zoid) <= aiDat[index].melee_range) {
                if (aiDat[index].near_action == 1) {
                    if (zdAI_IsAtack(index) == 1 && aiDat[index].melee_cooldown <= 0) {
                        if (index != 2 || zoid->target_slot != 0) {
                            zdAI_Atack1(index);
                            if (aiDat[index].melee_left > 0) {
                                aiDat[index].melee_left--;
                            } else {
                                aiDat[index].melee_cooldown = aiDat[index].melee_cooldown_time;
                                aiDat[index].melee_left = aiDat[index].melee_burst;
                            }
                        }
                    } else if (index != 2 || zoid->target_slot != 0) {
                        aiDat[index].command_timer = 60;
                        if (TARGET_DIST(zoid) < 20.0f) {
                            if (zdAI_IsTarget(index))
                                zdAI_Look(index);
                        } else {
                            zdAI_SetLenIn(index, 15.0f);
                            zdAI_SetAngleSpd(index, -10);
                        }
                        aiDat[index].fire_timer = 90;
                        zdAI_WeaponFire1(index);
                    }
                }
                if (aiDat[index].near_action == 3) {
                    aiDat[index].command_timer = 180;
                    zdAI_SetLenOut(index, 100.0f);
                    zdAI_SetAngleON(index, 180);
                }
                aiDat[index].command_timer += AI_RAND();
            } else if (index != 2 || zoid->target_slot != 0) {
                if (TARGET_DIST(zoid) <= aiDat[index].melee_range) {
                    zdAI_WeaponFireON(index);
                    aiDat[index].fire_timer = 90;
                    zdAI_WeaponFire1(index);
                }
            }

            if (aiDat[index].target_facing_me == 1 && TARGET_DIST(zoid) <= aiDat[index].melee_range) {
                if (aiDat[index].faced_action == 1)
                    zdAI_Jump(index);
                if (aiDat[index].faced_action == 2 || aiDat[index].faced_action == 4 || aiDat[index].faced_action == 7) {
                    if (aiDat[index].target_ahead == 1) {
                        if (aiDat[index].side == 1)
                            zdAI_Step(index, 90);
                        else
                            zdAI_Step(index, 270);
                    } else {
                        zdAI_Step(index, 180);
                    }
                    if (aiDat[index].faced_action == 4 && aiDat[index].len_out_timer == 0) {
                        aiDat[index].len_out_timer = 300;
                        aiDat[index].command_timer = 180;
                        zdAI_SetLenOut(index, 100.0f);
                        zdAI_SetAngleSpd(index, -10);
                        if (aiDat[index].faced_action == 7)
                            aiDat[index].len_in_timer = 30;
                    }
                }
                if (aiDat[index].faced_action == 5 || aiDat[index].faced_action == 6) {
                    zdAI_Jump(index);
                    if (aiDat[index].len_out_timer == 0) {
                        aiDat[index].len_out_timer = 300;
                        aiDat[index].command_timer = 180;
                        zdAI_SetLenOut(index, 100.0f);
                        zdAI_SetAngleSpd(index, -10);
                        if (aiDat[index].faced_action == 6)
                            aiDat[index].len_in_timer = 30;
                    }
                }
                if (aiDat[index].field_4C == 1)
                    aiDat[index].fire_timer = 30;
            }

            if (zoid->speed == 0.0f) {
                if (aiDat[index].stopped_timer == 0 || aiDat[index].ground_rise > 5) {
                    aiDat[index].stopped_timer = 180;
                    zdAI_Jump(index);
                } else {
                    aiDat[index].stopped_timer--;
                    if (aiDat[index].stopped_timer < 0)
                        aiDat[index].stopped_timer = 0;
                    if (aiDat[index].step_timer == 0) {
                        aiDat[index].step_timer = 60;
                        if (zoid_ai->target_angle > 160.0f && zoid_ai->target_angle < 200.0f)
                            zdAI_Step(index, 90);
                        else
                            zdAI_Step(index, 180);
                    } else {
                        aiDat[index].step_timer--;
                        if (aiDat[index].step_timer < 0)
                            aiDat[index].step_timer = 0;
                    }
                }
            }

            if (aiDat[index].len_in_timer > 0 && aiDat[index].len_out_timer == 0)
                aiDat[index].len_in_timer--;
            if (aiDat[index].len_in_timer == 0 && aiDat[index].len_out_timer == 0) {
                aiDat[index].len_in_timer = -1;
                aiDat[index].command_timer = 180;
                if (zdAI_IsTarget(index)) {
                    aiDat[index].fire_timer = 90;
                    zdAI_WeaponFire1(index);
                }
                if (aiDat[index].side == 1) {
                    zdAI_SetLenIn(index, 15.0f);
                    zdAI_SetAngleSpd(index, 10);
                } else {
                    zdAI_SetLenIn(index, 15.0f);
                    zdAI_SetAngleSpd(index, -10);
                }
            }

            if (zoid_ai->partner_command == AI_PARTNER_ATTACK_LOCKED && index == 2) {
                zdAI_SetZoid0(index, Zoid[0].target_slot);
                aiDat[index].command_timer = 600;
                zoid_ai->partner_command = AI_PARTNER_NONE;
                OSReport("AI [1]\223GZoid[0].lockZoid\202\360\215U\214\202\n");
            }
            if (zoid_ai->partner_command == AI_PARTNER_COME_NEAR && index == 2 && aiDat[index].command_timer == 0) {
                zdAI_TargetNext(index);
                zdAI_SetZoid0(index, 0);
                zdAI_SetLenIn(index, 60.0f);
                zdAI_SetAngleON(0, -120);
                aiDat[index].command_timer = 600;
                zoid_ai->partner_command = AI_PARTNER_NONE;
                OSReport("AI \216\251\225\252\202\311\213\337\202\303\202\304\215\266120\201\213\202\326\n");
            }
            if (zoid_ai->partner_command == AI_PARTNER_KEEP_DISTANCE && index == 2 && aiDat[index].command_timer == 0) {
                zdAI_WeaponFire1(index);
                zdAI_SetLenOut(index, 200.0f);
                aiDat[index].command_timer = 600;
                zoid_ai->partner_command = AI_PARTNER_NONE;
                OSReport("AI \223G\202\306\202\314\213\227\227\243\202\360\202\306\202\351\n");
            }
            if (zoid_ai->partner_command == AI_PARTNER_CLOSE_COMBAT && index == 2 && aiDat[index].command_timer == 0) {
                if (zoid_ai->field_70 >= 0)
                    OSReport("AI Target\202\240\202\350 %d\n", zoid_ai->field_70);
                zdAI_SetLenIn(index, 50.0f);
                aiDat[index].command_timer = 600;
                zoid_ai->partner_command = AI_PARTNER_NONE;
                OSReport("AI \220\332\213\337\220\355\203\202\201[\203h\202\326\n");
            }

            if (zdAI_WarningArea(index) == 1) {
                zdAI_SearchEnemy(index);
                zdAI_SetZoid(index);
                zdAI_SetZoid0(index, zoid->target_slot);
                aiDat[index].fire_timer = 120;
                zdAI_WeaponFire1(index);
                zdAI_WeaponFireON(index);
                zdAI_goPoint(index, 0.0f, 0.0f);
                aiDat[index].command_timer = 180;
                OSReport("AI \220\355\223\254\203G\203\212\203A\212O%d\201FPOint0,0\n", index);
            }

            if (zoid->health < zoid->previous_health && aiDat[index].command_timer == 0) {
                aiDat[index].fire_timer = 90;
                if (zdAI_IsTarget(index)) {
                    zdAI_WeaponFire1(index);
                } else {
                    ang = zdAI_WeaponGetID(index);
                    bullet = Tea_partsdat[ang].bullets[0];
                    zdAI_WeaponFire1(index);
                    if (Tea_bulletdat[bullet].kind == BULLET_KIND_AT20) {
                        zdAI_WeaponFireON(index);
                    } else {
                        zdAI_WeaponFireOFF(index);
                        aiNextWeapon(index);
                    }
                }
                aiDat[index].command_timer = 600;
            }
        }
    }
}
