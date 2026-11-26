#pragma readonly_strings on
#include "ttl_main_data.h"

extern s32 VolSe, VolBgm, VolVoice;
extern s16 TEA_SEVOL, TEA_BGMVOL, TEA_VOICEVOL;
extern void OSReport(const char *format, ...);

void configSet(void)
{
    TEA_VOICEVOL = VolVoiceTBL[VolVoice];
    TEA_BGMVOL = VolBgmTBL[VolBgm];
    TEA_SEVOL = VolSeTBL[VolSe];
    OSReport("config voice  volume %d  bgm%d\n", VolVoice, VolBgm);
}
