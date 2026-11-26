#include "weapon.h"

extern void PurgeArc(void *archive);

void sLsrEpilogue(void)
{
    s32 i;
    ModelArchive *archive;
    for (i = 0; i < 11; i++) {
        archive = sLsr[i].archive;
        if (archive != 0) {
            PurgeArc(archive);
            sLsr[i].archive = 0;
            sLsr[i].source = 0;
        }
    }
}
