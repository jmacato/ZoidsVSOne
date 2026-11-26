#include "weapon.h"

void sLsrSet(HSD_JObj *source, ModelArchive *archive)
{
    s32 i;
    s32 r;
    s32 c;
    Lsr *lsr;

    if (source == 0)
        return;
    if (archive == 0)
        return;
    for (i = 0; i < 11; i++) {
        lsr = &sLsr[i];
        if (lsr->archive == 0) {
            lsr->source = source;
            for (r = 0; r < 3; r++) {
                for (c = 0; c < 4; c++) {
                    lsr->start[r][c] = source->matrix[r][c];
                    lsr->end[r][c] = source->matrix[r][c];
                }
            }
            lsr->archive = archive;
            return;
        }
    }
}
