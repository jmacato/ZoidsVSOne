#include "types.h"

extern s32 TeaVoiceFlag[64];
extern u32 TeaVoiceId[64];
extern u8 TeaVoiceNum;
extern u32 sndFXCheck(u32 id);

u8 TEA_VoiceNumChk(void)
{
    s32 i;
    s32 count = 0;

    for (i = 0; i < 64; i++) {
        if (TeaVoiceFlag[i] != 0) {
            u32 id = TeaVoiceId[i];

            if (sndFXCheck(id) == 0xFFFFFFFF) {
                TeaVoiceId[i] = id;
                TeaVoiceFlag[i] = 0;
            } else {
                count++;
            }
        }
    }
    TeaVoiceNum = count;
    return count;
}
