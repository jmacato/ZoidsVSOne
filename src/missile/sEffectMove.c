#include "missile.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sEffectFollow(Effect *effect);
extern void sEffectTrace(Effect *effect);
extern void sEffectZoid(Effect *effect);
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

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void sEffectMove(Effect *effect)
{
    s32 kind;
    s32 r;
    s32 c;

    if (effect == NULL)
        return;
    if (effect->root == NULL)
        return;
    if (effect->type <= 0)
        return;
    kind = Tea_effectdat[effect->type].kind;
    if (effect->mode == 3 || effect->mode == 2) {
        if (effect->source != NULL) {
            for (r = 0; r < 3; r++) {
                for (c = 0; c < 4; c++)
                    effect->root->matrix[r][c] = effect->source->matrix[r][c];
                effect->position[r] = effect->source->matrix[r][3];
            }
            sGlobal2Local(effect->root);
        }
    }
    if (effect->mode == 3)
        kind = EFFECT_KIND_ZOID;
    HSD_JObjSetTranslateX(effect->root, effect->position[0]);
    HSD_JObjSetTranslateY(effect->root, effect->position[1]);
    HSD_JObjSetTranslateZ(effect->root, effect->position[2]);
    sMakeMatrix(effect->root);
    if (effect->joints[0].joint != NULL) {
        if (kind == EFFECT_KIND_FOLLOW)
            sEffectFollow(effect);
        if (kind == EFFECT_KIND_TRACE)
            sEffectTrace(effect);
        if (kind == EFFECT_KIND_ZOID)
            sEffectZoid(effect);
    }
}
