#include "int_se.h"

extern IntSeEntry IntSe[12];

void IntSeClear(void)
{
    s32 i;

    for (i = 0; i < 12; i++) {
        if (IntSe[i].se != 0) {
            if (IntSe[i].timer != 0) {
                IntSe[i].timer--;
            }
            if (IntSe[i].timer == 0) {
                IntSe[i].se = 0;
            }
        }
    }
}
