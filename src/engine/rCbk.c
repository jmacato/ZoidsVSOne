#include "dvd_file.h"

extern s32 rCbkR;

void rCbk(s32 result, DVDFileInfo *file)
{
    rCbkR = 3;
}
