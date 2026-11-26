#include "missile.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjDispAll(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);
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

void sEffectDispAll(void)
{
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 100; i++) {
        if (sEffect[i].root == 0)
            continue;
        if (sEffect[i].mode == 2 && sEffect[i].source != 0) {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 4; k++) {
                    sEffect[i].root->matrix[j][k] = sEffect[i].source->matrix[j][k];
                }
                sEffect[i].position[j] = sEffect[i].source->matrix[j][3];
            }
            sGlobal2Local(sEffect[i].root);
        }
        HSD_JObjSetTranslateX(sEffect[i].root, sEffect[i].position[0]);
        HSD_JObjSetTranslateY(sEffect[i].root, sEffect[i].position[1]);
        HSD_JObjSetTranslateZ(sEffect[i].root, sEffect[i].position[2]);
        HSD_JObjDispAll(sEffect[i].root, 0, 7, 0);
    }
}
