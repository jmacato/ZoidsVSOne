#include "zoid_ai.h"

extern s32 sCamNN;

void ZoidAI(void)
{
    ZoidState *zoid;
    s32 first = 1;
    s32 index;

    if (sCamNN != 1) {
        first = 2;
    }
    Zoid[0].ai_active = 0;
    Zoid[1].ai_active = 0;
    for (index = first, zoid = &Zoid[index]; index < 16; zoid++, index++) {
        if (zoid->joint != 0 && zoid->death_started == 0) {
            zoid->ai_active = 1;
            ai(index);
        }
    }
    for (index = 0, zoid = Zoid; index < 16; index++, zoid++) {
        ZoidState *current = zoid;

        if (current->death_started == 0) {
            zdExecAI(current);
        }
    }
}
