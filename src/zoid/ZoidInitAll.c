#include "zoid.h"
#include "game_mode.h"
#include "map_info.h"
#include "game_zoid_entry.h"

ZoidState Zoid[16];
extern char mgI[];
extern void ZoidInit1(ZoidState *zoid, s32 index, s32 team);
extern s32 infoLoadZoid0(ZoidState *zoid, void *info);
extern s32 infoLoadZoid1(ZoidState *zoid, void *info);
extern s32 infoLoadZoid(ZoidState *zoid, void *info);
extern f32 sColPosY(Vec3 *point, u16 *selector);

void ZoidInitAll(void)
{
    s32 unused[2];
    s32 n;
    s32 human;
    s32 i;
    MapInfoUnit *unit;
    s32 result;
    s32 slots[17];
    ZoidState *zoid;
    s32 team;

    for (i = 0; i < 16; i++) {
        if (GameZoid[i].type == -1)
            continue;
        if (i < 5)
            team = 0;
        else
            team = 1;
        if (team == 1 && (GameMode.game_type == GAME_TYPE_BATTLE || GameMode.game_type == GAME_TYPE_MISSION))
            continue;
        n = (i % 5) * 2 + team;
        ZoidInit1(&Zoid[n], i, team);
    }
    if (GameMode.game_type == GAME_TYPE_VS)
        return;
    if (GameMode.game_type == GAME_TYPE_3)
        return;
    for (i = 0; i < 17; i++) {
        unit = &((MapInfo *)mgI)->units[i];
        switch (unit->kind) {
        case MAP_UNIT_MAP:
        case 2:
            break;
        case MAP_UNIT_ZOID:
        case MAP_UNIT_PLAYER:
        case MAP_UNIT_PARTNER:
            zoid = 0;
            if (unit->kind == MAP_UNIT_ZOID) {
                zoid = 0;
                if (unit->enabled != 0) {
                    human = (s8)unit->field_111;
                    for (n = human + 1; n < 16; n += 2) {
                        if (Zoid[n].joint == 0)
                            break;
                    }
                    if (n >= 16)
                        continue;
                    if (Zoid[n].joint != 0)
                        continue;
                    zoid = &Zoid[n];
                    if (unit->kind == MAP_UNIT_ZOID)
                        result = infoLoadZoid0(zoid, &unit->zoid);
                    else
                        result = infoLoadZoid(zoid, &unit->zoid);
                    if (result == 0) {
                        slots[i] = -1;
                        zoid = 0;
                    } else {
                        slots[i] = n;
                    }
                    zoid->slot = (human + 1) & 1;
                }
            }
            if (unit->kind == MAP_UNIT_PLAYER)
                zoid = &Zoid[0];
            if (unit->kind == MAP_UNIT_PARTNER)
                zoid = &Zoid[2];
            if (zoid != 0) {
                zoid->position[0] = unit->x;
                zoid->position[2] = unit->z;
                zoid->position[1] = 100.0f;
                zoid->position[1] = sColPosY((Vec3 *)zoid->position, 0) + 1.0f;
            }
            break;
        }
    }
    for (i = 0; i < 17; i++) {
        unit = &((MapInfo *)mgI)->units[i];
        switch (unit->kind) {
        case MAP_UNIT_MAP:
            break;
        case MAP_UNIT_ZOID:
            if (unit->kind == MAP_UNIT_ZOID && unit->enabled != 0 && slots[i] != -1 && Zoid[slots[i]].joint != 0)
                infoLoadZoid1(&Zoid[slots[i]], &unit->zoid);
            break;
        case 2:
            break;
        }
    }
}
