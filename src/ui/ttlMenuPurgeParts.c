#include "types.h"
#include "model_archive.h"

extern void *menu1p;
extern void HSD_VIWaitXFBFlush(void);

void ttlMenuPurgeParts(void)
{
    if (menu1p != 0) {
        PurgeArc2(menu1p);
        menu1p = 0;
    }
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
}
