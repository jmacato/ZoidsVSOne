#include "types.h"

typedef struct VoiceSequence {
    s32 voice;
    s32 sequence[19];
} VoiceSequence;

extern VoiceSequence voiceSn[5];
extern s32 voiceSn2[20];

s32 voiceSn2c1(s32 index)
{
    VoiceSequence *entry;
    s32 i;

    entry = &voiceSn[index];
    for (i = 0; i < 20; i++) {
        if (entry->sequence[i] == -1)
            break;
        if (entry->sequence[i] != voiceSn2[i])
            return -1;
    }
    return entry->voice;
}
