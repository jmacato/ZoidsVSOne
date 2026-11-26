#include "zoid_ai.h"

extern void zdAtack1(ZoidState *zoid);

void zdAI_Atack1(s32 index)
{
    if (index >= 0 && index < 16) {
        zdAtack1(&Zoid[index]);
    }
}
