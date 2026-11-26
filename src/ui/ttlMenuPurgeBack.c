#include "types.h"
#include "model_archive.h"

extern void *menu_back1p;
extern void HSD_VIWaitXFBFlush(void);

void ttlMenuPurgeBack(void)
{
    if (menu_back1p != 0) {
        PurgeArc2(menu_back1p);
        menu_back1p = 0;
    }
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
}
