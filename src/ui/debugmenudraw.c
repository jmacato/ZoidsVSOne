#include "types.h"

extern void HSD_VICopyXFB(s32 mode);
extern void HSD_VISetXFBDrawDone(void);
extern void VIWaitForRetrace(void);

void debugmenudraw(void)
{
    HSD_VICopyXFB(0);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
}
