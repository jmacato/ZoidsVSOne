#include "game_save.h"

extern void OSReport(const char *format, ...);

void shopDispParts(s32 record)
{
    GameSaveRecord *save = &IveSave[record];
    s32 i;

    OSReport("parts --- ");
    for (i = 0; i < 450; i++) {
        if (save->owned_parts[i] > 0) {
            if (i == save->owned_part_count)
                OSReport(" : ");
            OSReport("%3d ", save->owned_parts[i]);
        }
    }
    OSReport(" --- \n");
}
