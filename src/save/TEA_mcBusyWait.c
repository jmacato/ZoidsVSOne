#include "card.h"

extern u32 __OSBusClock : 0x800000F8;
extern s32 MemCardStatus[2];
extern s64 OSGetTime(void);
extern void OSReport(const char *format, ...);

s32 TEA_mcBusyWait(s32 channel)
{
    s32 result;
    s32 printed = 0;
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;

    while ((result = CARDGetResultCode(channel)) == CARD_RESULT_BUSY) {
        if (printed == 0) {
            OSReport("\245\245Busy\245\245");
        } else {
            printed = 1;
        }
        if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[channel] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
    }
    if (result == CARD_RESULT_READY) {
        return 1;
    }
    return 0;
}
