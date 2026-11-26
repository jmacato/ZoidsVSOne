#include "zoid.h"
#include "game_mode.h"

s32 calcEndVsMan(void)
{
    ZoidState *first = &Zoid[0];
    ZoidState *second = &Zoid[1];
    if (first->death_started == 0) {
        if (second->death_started == 0)
            return GAME_RESULT_NONE;
        return GAME_RESULT_WIN;
    }
    if (second->death_started == 0)
        return GAME_RESULT_LOSE;
    return GAME_RESULT_DRAW;
}
