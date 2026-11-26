#include "game_pad.h"
#include "ttl_main_data.h"

extern PadState *sPad1;
extern s32 VolVoice;
extern s32 TestVoice;
extern s16 TEA_VOICEVOL;
extern void TEA_VoiceOn(u8 character, s16 voice);

void sub2(void)
{
    if (sPad1->left != 0)
        VolVoice--;
    if (sPad1->right != 0)
        VolVoice++;
    if (VolVoice < 0)
        VolVoice = 0;
    if (VolVoice >= 10)
        VolVoice = 10;
    TEA_VOICEVOL = VolVoiceTBL[VolVoice];
    if (sPad1->pressed_a != 0)
        TEA_VoiceOn(samplevoiceno[TestVoice].character, samplevoiceno[TestVoice].voice);
}
