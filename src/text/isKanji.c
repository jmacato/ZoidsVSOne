#include "types.h"
s32 isKanji(u8 character)
{
    u32 lead = character & 0xe0;
    return lead == 0xe0 || lead == 0x80;
}
