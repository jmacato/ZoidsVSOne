#include "model_archive.h"
#include "game_pad.h"
#include "map_info.h"

/* first 0x120 bytes of a MapInfoUnit */
typedef struct MapUnit {
    char name[0x20];
    s32 kind;
    char picture[0x28];
    char text[0x64];
    s32 x;
    s32 y;
    s32 z;
    s8 enabled;
    u8 reserved_BD[3];
    s32 zoid;
    u8 reserved_C4[76];
    s8 chara;
    u8 human;
    u8 reserved_112[14];
} MapUnit;

/* MapInfo in 588-byte steps; slot[i].unit is MapInfo.units[i] */
typedef struct MapUnitSlot {
    u8 reserved_000[300];
    MapUnit unit;
} MapUnitSlot;

extern s32 enemyChara[2];
extern s32 enemyZoid[2];
extern PadState *sPad1;
extern MapInfo *rdMapInfo(s32 mode, s32 map);
extern void sPadAll(void);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 jobjAnim(HSD_JObj *joint);
extern void GXInvalidateVtxCache(void), GXInvalidateTexAll(void);
extern void SeCat(void), SeRet(void);
extern void HSD_SetZSortMode(s32, s32);
extern void HSD_StateInvalidate(s32);
extern void menu_sDispBattleNextYokok(MapInfo *info, ModelArchive *picture, ModelArchive *background);

void yokoku(s32 map)
{
    char path[200];
    MapInfo *info = rdMapInfo(0, map);
    ModelArchive *picture;
    ModelArchive *background;
    MapUnitSlot *unit;
    s32 *chara;
    s32 *zoid;
    s32 count;
    s32 i;

    sPadAll();
    if (info == 0)
        return;
    unit = (MapUnitSlot *)info;
    count = 0;
    chara = enemyChara;
    zoid = enemyZoid;
    for (i = 0; i < 17; i++, unit++) {
        MapUnit *data;

        if (count == 2)
            break;
        data = &unit->unit;
        if (unit->unit.kind == MAP_UNIT_ZOID && data->enabled != 0 && (s32)data->human != 1) {
            *chara++ = data->chara;
            count++;
            *zoid++ = data->zoid;
        }
    }
    if (info->units[0].picture[0] == 0) {
        picture = 0;
    } else {
        sprintf(path, "menu/picture/%s.dat", info->units[0].picture);
        picture = LoadArc2(path);
        if (picture != 0) {
            SetAnimArc2(picture, 0, 0);
            jobjAnim(picture->models[0]);
        }
    }
    background = LoadArc2("menu/vs_menu/new/bglogo.dat");
    GXInvalidateVtxCache();
    GXInvalidateTexAll();
    SeCat();
    HSD_SetZSortMode(0, 0);
    HSD_StateInvalidate(-1);
    HSD_SetZSortMode(0, 0);
    do {
        menu_sDispBattleNextYokok(info, picture, background);
        sPadAll();
    } while (sPad1->pressed_b == 0 && sPad1->pressed_a == 0);
    SeRet();
    if (background != 0)
        PurgeArc2(background);
    if (picture != 0)
        PurgeArc2(picture);
}
