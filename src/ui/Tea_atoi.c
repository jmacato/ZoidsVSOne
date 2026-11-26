#include "types.h"

s32 Tea_atoi(u8 text[6])
{
    s32 scale[6] = {1, 10, 100, 1000, 10000, 100000};
    s32 unused[1];
    s32 i;
    s32 value;
    s8 digit;
    u8 c;

    value = 0;
    for (i = 0; i < 6; i++) {
        c = text[5 - i] - '0';
        (void)(c + 1);
        digit = text[5 - i];
        digit = digit - '0';
        if (digit == 10)
            digit = 0;
        value += digit * scale[i];
    }
    return value;
}
