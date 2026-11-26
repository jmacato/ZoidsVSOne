#include "game_mode.h"

extern void debug11(void);
extern void OSReport(const char *format, ...);
extern void hokyuu(s32 map);

void ttlMenu_sDispMissionHokyu(void)
{
    debug11();
    OSReport("hokyu start   --------\n");
    hokyuu(GameMode.map);
    OSReport("map no= %d\n", GameMode.map);
    debug11();
}
