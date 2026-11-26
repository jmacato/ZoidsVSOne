#include "types.h"

extern s64 OSGetTime(void);
extern void OSReport(const char *format, ...);

s32 TEA_mcFileClose(void)
{
    OSGetTime();
    OSReport("MemCardClose\t");
    OSReport("Done\n");
    return 1;
}
