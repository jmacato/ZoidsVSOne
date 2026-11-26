#include "types.h"

extern s32 voiceSn2[20];

void voiceSn2i(void)
{
    s32 index;

    for (index = 0; index < 20; index++) {
        voiceSn2[index] = -1;
    }
}
