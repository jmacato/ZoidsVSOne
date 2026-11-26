#include "game_mode.h"
extern s32 menufnc_MapInfo(s32 mode, s32 map);

s32 menufncZoidMission_MapInfo(void)
{
    return menufnc_MapInfo(1, GameMode.map);
}
