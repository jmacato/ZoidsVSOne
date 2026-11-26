#include "zoid.h"

extern void ZoidCoObjMtxI(ZoidState *zoid);
extern s32 ZoidCoObjCoObj(CoObj *a, CoObj *b, s32 flags);

void ZoidZdCoObjBodyAll(void)
{
    s32 i;
    s32 j;

    for (i = 0; i < 16; i++) {
        ZoidState *zoid = &Zoid[i];

        if (zoid->joint != 0 && zoid->body_coobj.joint != 0) {
            ZoidCoObjMtxI(zoid);
        }
    }
    for (i = 0; i < 16; i++) {
        ZoidState *zoid = &Zoid[i];

        if (zoid->joint != 0 && zoid->body_coobj.joint != 0) {
            for (j = 0; j < 16; j++) {
                ZoidState *other = &Zoid[j];

                if (i != j && other->joint != 0 && other->body_coobj.joint != 0) {
                    s32 hit = ZoidCoObjCoObj(&zoid->body_coobj, &other->body_coobj, 0);

                    zoid->contact[j] = hit;
                    other->contact[i] = hit;
                }
            }
        }
    }
}
