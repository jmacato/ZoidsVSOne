#include "card.h"

extern s32 MemCardStatus[2];
extern s32 MemCardOn[2];

s32 TEA_mcChkBroken(s32 channel)
{
    s32 result = CARDCheckAsync(channel, 0);
    MemCardStatus[channel] = result;
    if (result == CARD_RESULT_BROKEN) {
        MemCardOn[channel] = 0;
        return 0;
    }
    return 1;
}
