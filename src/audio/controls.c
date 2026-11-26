#include "audio.h"

extern u32 TeaSeqId;

s32 TEA_VidChk(u32 voice)
{
    return HSD_AudioSFXCheck(voice) == (u32)-1 ? 0 : 1;
}

void TEA_VidOff(u32 voice)
{
    HSD_AudioSFXKeyOff(voice);
}

#pragma dont_inline on
void TEA_AudioSeqVolume(u32 volume, u16 time, u8 mode)
{
    u8 value = volume;
    s32 sequence;
    if (TeaSeqId != (u32)-1)
        HSD_AudioSeqVolume(value, time, TeaSeqId, mode);
    for (sequence = 0; sequence < 10000; sequence++) {
        HSD_AudioSeqVolume(value, time, sequence, mode);
    }
}
#pragma dont_inline reset

void TEA_AudioSeqVol(u32 volume, u16 time)
{
    TEA_AudioSeqVolume(volume, time, 0);
}

void TEA_AudioSeqFree(void)
{
    s32 sequence;
    if (TeaSeqId != (u32)-1)
        HSD_AudioSeqFree(TeaSeqId);
    for (sequence = 0; sequence < 10000; sequence++) {
        HSD_AudioSeqFree(sequence);
    }
}

void TEA_AudioSeqStop(void)
{
    s32 sequence;
    if (TeaSeqId != (u32)-1)
        HSD_AudioSeqStop(TeaSeqId);
    for (sequence = 0; sequence < 10000; sequence++) {
        HSD_AudioSeqStop(sequence);
    }
}

#pragma dont_inline on
s32 TEA_SeKeyOn(u16 effect, u8 volume, u8 pan, u32 unused)
{
    if (effect == -1)
        return -1;
    HSD_AudioSFXStartEx(effect, volume, pan, 0);
    return -1;
}

extern s16 TEA_SEVOL;

void SeRet(void)
{
    TEA_SeKeyOn(0x14F, TEA_SEVOL, 64, 64);
}

void SeRetDemo(void)
{
    TEA_SeKeyOn(0x220, TEA_SEVOL, 64, 64);
}

void SeCancel(void)
{
    TEA_SeKeyOn(0x1AB, TEA_SEVOL, 64, 64);
}

void SeSelectB(void)
{
    TEA_SeKeyOn(0x1B0, TEA_SEVOL, 64, 64);
}

void SeWinon(void)
{
    TEA_SeKeyOn(0x1F1, TEA_SEVOL, 64, 64);
}

void SeBuzzerC(void)
{
    TEA_SeKeyOn(0x1AD, TEA_SEVOL, 64, 64);
}

void SeLiftStart(void)
{
    TEA_SeKeyOn(0x219, TEA_SEVOL, 64, 64);
}

void SeLiftStop(void)
{
    TEA_SeKeyOn(0x14F, TEA_SEVOL, 64, 64);
}

void SeCat(void)
{
    TEA_SeKeyOn(0x13F, TEA_SEVOL, 64, 64);
}
