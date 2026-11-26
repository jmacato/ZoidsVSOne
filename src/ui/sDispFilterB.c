#include "model_archive.h"

extern ModelArchive *dspFilter;
extern s32 gameEndF;

void sDispFilterB(void)
{
    if (dspFilter == 0)
        return;
    if (dspFilter->models[0] == 0)
        return;
    if (gameEndF == 7)
        gameEndF = 8;
    if (gameEndF == 6)
        gameEndF = 7;
}
