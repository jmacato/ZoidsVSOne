#include "zoid.h"

extern void ZoidCoObjMtxI(ZoidState *zoid);
extern void sMissileZoid(void);

void ZoidCoObjAll(void)
{
    s32 i;
    s64 frame_padding;

    for (i = 0; i < 16; i++) {
        ZoidCoObjMtxI(&Zoid[i]);
    }
    sMissileZoid();
}
