#include "types.h"

u8 *cpyCr(u8 *source, u8 *destination)
{
    u8 value;
    while ((value = *source) != 0) {
        source++;
        if (value == 0 || value == 13)
            break;
        if (value != 10)
            *destination++ = value;
    }
    *destination = 0;
    return source;
}
