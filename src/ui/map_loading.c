#pragma readonly_strings on
#include "model_archive.h"
#include "game_mode.h"

extern ModelArchive *menu1p_map;
extern s32 fexist(char *name);
extern s32 sprintf(char *buffer, const char *format, ...);
extern void *rdMapInfo(s32 mode, s32 map);
extern void OSReport(const char *format, ...);

void menu_VsFarmMapLoad(s16 map)
{
    char filename[80];

    if (menu1p_map != 0) {
        PurgeArc2(menu1p_map);
        menu1p_map = 0;
    }
    sprintf(filename, "menu/picture/m%02d.dat", map);
    if (fexist(filename) == 1)
        menu1p_map = LoadArc2(filename);
}

void loadMapInfo(void)
{
    s32 mode, map, variant;

    if (GameMode.game_type == GAME_TYPE_BATTLE) {
        mode = 0;
        variant = GameMode.map_variant;
        if (variant < 0)
            variant = 0;
        if (variant > 2)
            variant = 2;
        if (GameMode.map_variant != variant)
            OSReport("mg  stage*3 + stage2  stage2 over(0,1,2)  is %d \n",
                     GameMode.map_variant);
        GameMode.map_variant = variant;
        map = GameMode.map * 3 + GameMode.map_variant;
    } else {
        mode = 1;
        map = GameMode.map;
    }
    if (GameMode.map != 100)
        rdMapInfo(mode, map);
}
