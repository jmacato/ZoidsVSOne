#include "joint.h"
#include "dobj.h"

#define RENDER_SHADOW (1 << 26)

extern HSD_DObj *HSD_JObjGetDObj(HSD_JObj *joint);

static inline HSD_MObj *HSD_DObjGetMObj(HSD_DObj *dobj)
{
    return dobj ? dobj->mobj : 0;
}

static inline HSD_DObj *HSD_DObjGetNext(HSD_DObj *dobj)
{
    return dobj ? dobj->next : 0;
}

void setModelShadow0(HSD_JObj *joint)
{
    HSD_DObj *dobj;
    for (dobj = HSD_JObjGetDObj(joint); dobj != 0; dobj = HSD_DObjGetNext(dobj))
        HSD_DObjGetMObj(dobj)->rendermode |= RENDER_SHADOW;
}
