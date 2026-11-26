#include "zoid.h"

extern void HSD_ShadowDeleteObject(void *shadow, HSD_JObj *jobj);
extern void ZoidShadowLo(void *shadow, ZoidState *zoid);

void shadowSetZoid(void *shadow, s32 index)
{
    ZoidState *zoid;
    s32 i;

    HSD_ShadowDeleteObject(shadow, 0);
    zoid = &Zoid[index];
    ZoidShadowLo(shadow, zoid);
    for (i = 0; i < 16; i++) {
        if (i != index && zoid->joint != 0 && !(zoid->distances[i] > 100.0f)) {
            ZoidShadowLo(shadow, &Zoid[i]);
        }
    }
}
