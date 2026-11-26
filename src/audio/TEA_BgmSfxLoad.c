#include "types.h"

extern s32 TeaSeqPlayFlag;
extern u8 TeaSoundSfxLoadNum;
extern void TEA_AudioSeqStop(void);
extern void TEA_AudioSeqFree(void);
extern void sReadPre(void);
extern void TEA_SoundSfxLoad(char *path, s32 group);
extern void TEA_SoundSfxPop(void);

void TEA_BgmSfxLoad(char *path, s32 group)
{
    s32 loaded = TeaSoundSfxLoadNum;
    if (TeaSeqPlayFlag == 1) {
        TEA_AudioSeqStop();
        TEA_AudioSeqFree();
        TeaSeqPlayFlag = 0;
    }
    if (loaded == 0) {
        sReadPre();
        TEA_SoundSfxLoad("audio/se/se", 8);
        loaded++;
    }
    if (loaded == 1) {
        sReadPre();
        TEA_SoundSfxLoad(path, group);
    } else {
        if (loaded > 1) {
            sReadPre();
            TEA_SoundSfxPop();
            sReadPre();
            TEA_SoundSfxLoad(path, group);
        }
        TeaSoundSfxLoadNum = loaded;
    }
}
