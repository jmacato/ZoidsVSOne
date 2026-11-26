#include "int_se.h"

extern IntSeEntry IntSe[12];

void IntSePrologue(void)
{
    s32 i;
    for (i = 0; i < 12; i++) {
        IntSe[i].se = 0;
    }
}
