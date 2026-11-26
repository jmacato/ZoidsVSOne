#include "game_mode.h"

extern void OSReport(const char *format, ...);
extern void menufnc_MapInfo(s32 mode, s32 map);

void menufncZoidBattle_MapInfo(void)
{
    OSReport("=================================\n stage=%d , stage2=%d \n=======================================\n",
             GameMode.map, GameMode.map_variant);
    menufnc_MapInfo(0, GameMode.map_variant + GameMode.map * 3);
}
