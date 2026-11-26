#include "types.h"
#include "game_mode.h"
#include "game_save.h"

extern s32 vOn44;
extern void TEA_VoiceOn(u8 character, s16 voice);
extern void OSReport(const char *format, ...);

void voiceSet(s32 outcome)
{
    s32 character;
    s32 voice;
    if (vOn44 == 0) {
        if (GameMode.game_type == GAME_TYPE_MISSION) {
            if (IveSave[0].country == 1)
                character = 42;
            else
                character = 41;
            if (outcome <= 1)
                voice = 83;
            else
                voice = 84;
            TEA_VoiceOn(character, voice);
            OSReport("chara =%d , vc =%d \n", character, voice);
        }
        vOn44 = 1;
    }
}
