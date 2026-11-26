#include "missile.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY))
        result = 1;
    return result;
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void sEffectFollow(Effect *effect)
{
    s32 i;
    s32 n;
    u8 frame_padding[40];

    if (effect->source == 0)
        return;
    if (effect->joints[0].joint == 0)
        return;
    if (effect->type <= 0)
        return;
    effect->history[0][0] = effect->root->matrix[0][3];
    effect->history[0][1] = effect->root->matrix[1][3];
    effect->history[0][2] = effect->root->matrix[2][3];
    for (i = 59; i > 0; i--) {
        effect->history[i][0] = effect->history[i - 1][0];
        effect->history[i][1] = effect->history[i - 1][1];
        effect->history[i][2] = effect->history[i - 1][2];
    }
    for (i = 17; i > 0; i--) {
        HSD_JObj *joint = effect->joints[i].joint;
        if (joint != 0) {
            joint->matrix[0][3] = effect->history[i * 3][0];
            joint->matrix[1][3] = effect->history[i * 3][1];
            joint->matrix[2][3] = effect->history[i * 3][2];
        }
    }
    {
        HSD_JObj *root = effect->root;
        HSD_JObj *joint = effect->joints[0].joint;
        if (root != 0 && joint != 0) {
            for (n = 0; n < 3; n++) {
                if (root->matrix[n][3] != joint->matrix[n][3])
                    break;
            }
            if (n == 3)
                joint->matrix[0][3] += 0.02;
            sGlobal2Local(joint);
        }
    }
    for (i = 1; i < 18; i++) {
        HSD_JObj *previous = effect->joints[i - 1].joint;
        HSD_JObj *joint = effect->joints[i].joint;
        if (previous != 0 && joint != 0) {
            for (n = 0; n < 3; n++) {
                if (previous->matrix[n][3] != joint->matrix[n][3])
                    break;
            }
            if (n == 3)
                joint->matrix[0][3] += 0.02;
            HSD_JObjSetScaleX(joint, 1.0f);
            sGlobal2Local(joint);
        }
    }
    sMakeMatrix(effect->root);
}
