#include "types.h"

extern s32 voiceSn2c1(s32 index);

s32 voiceSn2c(void)
{
    s32 i;
    s32 voice;
    for (i = 0; i < 5; i++) {
        voice = voiceSn2c1(i);
        if (voice != -1)
            return voice;
    }
    return -1;
}
