#include "ground_object.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern GroundObject obj[50];
extern void sGlobal2Local(HSD_JObj *joint);
extern s32 jobjAnim(HSD_JObj *joint);
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

static inline void HSD_JObjSetScaleY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 819, "jobj");
    jobj->scale.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void grdObjAnim(void)
{
    GroundObject *object;
    s32 r;
    s32 c;
    s32 i;

    for (i = 0; i < 50; i++) {
        object = &obj[i];
        if (obj[i].joint != NULL && obj[i].animation != GROUND_OBJECT_ANIM_INTACT && obj[i].animation != GROUND_OBJECT_ANIM_BROKEN) {
            sGlobal2Local(obj[i].joint);
            if (jobjAnim(object->joint) != 0 && obj[i].animation == GROUND_OBJECT_ANIM_BREAKING) {
                grdObjSetAnim(object, GROUND_OBJECT_ANIM_BROKEN);
                jobjAnim(object->joint);
            }
            for (r = 0; r < 3; r++) {
                for (c = 0; c < 4; c++)
                    object->joint->matrix[r][c] = obj[i].matrix[r][c];
            }
            sGlobal2Local(object->joint);
            HSD_JObjSetScaleY(object->joint, 1.0f);
        }
    }
}
