#include "types.h"

void MemCpy(u8 *source, u8 *destination, s32 size)
{
    while (size) {
        *destination++ = *source++;
        size--;
    }
}
