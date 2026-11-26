#include "card.h"

extern u32 MemCardSectorSize;
extern s32 MemcardNowSlot, MemCardStatus[2];
extern s32 TEA_mcResult(s32 result);
extern void OSReport(const char *format, ...);

s32 TEA_mcChkSector(s32 channel)
{
    MemcardNowSlot = channel;
    if (MemCardSectorSize != 8192) {
        TEA_mcResult(-110);
        OSReport("MemCard%d SECTOR \n", MemCardSectorSize);
        return 0;
    }
    OSReport("MemCard%d SECTOR \n", MemCardSectorSize);
    return 1;
}

s32 TEA_mcChkIoErr(s32 channel)
{
    s32 result = CARDCheckAsync(channel, 0);
    MemCardStatus[channel] = result;
    if (result < 0) {
        if (result == CARD_RESULT_IOERROR)
            return 0;
        if (result == CARD_RESULT_WRONGDEVICE)
            return 0;
    } else {
        return 1;
    }
    return 1;
}
