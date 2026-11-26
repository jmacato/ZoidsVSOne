#include "zoid.h"
#include "missile.h"

#define NULL 0

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);

void sEffectZoid(Effect *effect)
{
    f32 pad_stack[2];
    ZoidState *zoid;
    HSD_JObj *source;
    HSD_JObj *target;
    s32 i;
    s32 r;
    s32 c;

    if (effect->source == NULL)
        return;
    if (effect->type <= 0)
        return;
    zoid = effect->zoid;
    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    for (i = 0; i < 17; i++) {
        source = zoid->weapon_slots[i + 10].joint;
        if (source != NULL) {
            target = effect->joints[i].joint;
            if (target != NULL) {
                for (r = 0; r < 3; r++) {
                    for (c = 0; c < 4; c++) {
                        target->matrix[r][c] = source->matrix[r][c];
                    }
                }
                sGlobal2Local(target);
            }
        }
    }
    sMakeMatrix(effect->root);
}
