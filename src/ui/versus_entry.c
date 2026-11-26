#include "types.h"

extern void ttlMenuLoadPersonBanner(void), ttlMenuLoadZoidBanner(void);
extern void ttlMenuLoadBack(s32 mode), ttlMenuLoadParts(s32 mode);

s32 menufncZoidVs01(void)
{
    ttlMenuLoadPersonBanner();
    ttlMenuLoadZoidBanner();
    ttlMenuLoadBack(3);
    ttlMenuLoadParts(7);
    return 0x130;
}
