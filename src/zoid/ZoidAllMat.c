#include "zoid.h"

extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);

void ZoidAllMat(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != 0) {
            zdSetXYZ(&Zoid[i]);
            sMakeMatrix(Zoid[i].joint);
        }
    }
}
