#include "types.h"

extern s16 TEA_VOICEVOL;
extern s32 sReadPre(void);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 fexist(char *path);
extern void TEA_VoiceFilePlay(char *path, u8 volume, s32 mode);

void TEA_VoiceOn(u8 character, s16 voice)
{
    char path[80];
    s32 exists;
    sReadPre();
    sprintf(path, "voice/%02d/V%02d_%02d.adp", character, character, voice);
    exists = fexist(path);
    if (exists == 1)
        TEA_VoiceFilePlay(path, TEA_VOICEVOL, 0);
}
