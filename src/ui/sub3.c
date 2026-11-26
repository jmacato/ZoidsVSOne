#pragma readonly_strings on
#include "game_pad.h"

extern PadState *sPad1;
#include "game_save.h"

typedef struct SampleVoice {
    u8 character;
    u8 reserved_1;
    s16 voice;
} SampleVoice;

extern s32 TestVoice;
extern SampleVoice samplevoiceno[];
extern GameSaveRecord IveSaveFlag;
extern void TEA_VoiceOn(u8 character, s16 voice);
extern void voiceSn2a(s32 voice);
extern s32 voiceSn2c(void);
extern void OSReport(const char *format, ...);

void sub3(void)
{
    s32 flag;

    if (sPad1->left != 0)
        TestVoice--;
    if (sPad1->right != 0)
        TestVoice++;
    if (TestVoice < 0)
        TestVoice = 0;
    if (TestVoice >= 99U)
        TestVoice = 99;
    if (sPad1->pressed_a != 0) {
        TEA_VoiceOn(samplevoiceno[TestVoice].character, samplevoiceno[TestVoice].voice);
        voiceSn2a(TestVoice);
        flag = voiceSn2c();
        if (flag != -1) {
            OSReport("add sys-flag[%d] \n", flag);
            IveSaveFlag.system_flags[flag] = 1;
        }
    }
}
