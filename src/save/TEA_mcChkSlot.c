#include "card.h"

extern s32 MemcardNowSlot;
extern s32 MemCardStatus[2];
extern s32 MemCardSectorSize;
extern s32 MemCardFreeSize;
extern s32 MemCardFreeDir;
extern s32 MemCardOn[2];
extern s64 OSGetTime(void);
extern s32 TEA_mcError(s32 slot, s32 result);

s32 TEA_mcChkSlot(s32 slot)
{
    s32 memSize = 4;
    s32 sectorSize = 8;
    s32 frame_padding[1];
    s64 time = OSGetTime();
    s32 result;
    s32 ready;

    MemcardNowSlot = slot;
    ready = 0;
    for (;;) {
        result = CARDProbeEx(slot, &memSize, &sectorSize);
        if (result != CARD_RESULT_BUSY)
            break;
        while (CARDGetResultCode(0) == CARD_RESULT_BUSY)
            ;
        MemCardStatus[0] = ready;
    }
    if (result == CARD_RESULT_READY) {
        MemCardSectorSize = sectorSize;
        CARDFreeBlocks(slot, &MemCardFreeSize, &MemCardFreeDir);
        MemCardStatus[0] = CARD_RESULT_READY;
        return 1;
    }
    if (result == CARD_RESULT_WRONGDEVICE) {
        TEA_mcError(slot, result);
        MemCardStatus[0] = CARD_RESULT_WRONGDEVICE;
        return 1;
    }
    if (result == CARD_RESULT_NOCARD) {
        MemCardStatus[0] = CARD_RESULT_NOCARD;
        MemCardOn[slot] = 0;
        return 0;
    }
    MemCardOn[slot] = 0;
    return 0;
}
