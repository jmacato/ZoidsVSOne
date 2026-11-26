#include "types.h"

extern s32 MemcardNowSlot;
extern s32 TEA_mcFileOpen(void);
extern s32 TEA_mcFileClose(void);

s32 TEA_mcFileExist(s32 slot)
{
    MemcardNowSlot = slot;
    if (TEA_mcFileOpen() == 0)
        return 0;
    TEA_mcFileClose();
    return 1;
}
