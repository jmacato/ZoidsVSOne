#include "types.h"

void ZeroMemory(void *memory, s32 size)
{
    u8 *byte = memory;
    s32 offset;

    for (offset = 0; offset < size; offset++) {
        *byte = 0;
        byte++;
    }
}
