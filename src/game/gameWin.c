#include "game_mode.h"

extern s32 calcEnd(void);

s32 gameWin(void)
{
    s32 result;

    result = calcEnd();
    if (result == GAME_RESULT_NONE) {
        result = GAME_RESULT_DRAW;
    }
    return result;
}
