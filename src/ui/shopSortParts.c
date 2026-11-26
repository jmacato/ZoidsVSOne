#include "game_save.h"

void shopSortParts(s32 record)
{
    s32 count;
    s32 j;
    GameSaveRecord *save = &IveSave[record];
    s32 i;
    s32 part;

    for (i = 0, count = 0; i < 450; i++) {
        if (save->owned_parts[i] <= 0)
            save->owned_parts[i] = 0;
        else
            count++;
    }
    for (i = 0; i < 449; i++) {
        part = save->owned_parts[i];
        if (part <= 0) {
            for (j = i + 1; j < 450; j++) {
                s16 value = save->owned_parts[j];

                if (value > -1) {
                    save->owned_parts[i] = value;
                    save->owned_parts[j] = part;
                    break;
                }
            }
        }
    }
    IveSave[0].owned_part_count = count;
}
