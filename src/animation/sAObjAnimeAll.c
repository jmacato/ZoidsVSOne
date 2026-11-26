#pragma readonly_strings on
#include "joint.h"
#include "aobj.h"

extern void __assert(const char *file, u32 line, const char *condition);
extern HSD_AObj *getAnimAobj(HSD_JObj *joint);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern u32 HSD_AObjGetFlags(HSD_AObj *aobj);
extern void setAnimFrame(HSD_JObj *joint, f32 frame);
extern void setAnimRate(HSD_JObj *joint, f32 rate);

static inline f32 HSD_AObjGetCurrFrame(HSD_AObj *aobj)
{
    if (aobj == 0)
        __assert("aobj.h", 149, "aobj");
    return aobj->current_frame;
}

static inline u32 sAObjGetFlags(HSD_AObj *aobj)
{
    u32 flags = HSD_AObjGetFlags(aobj);

    return flags;
}

s32 sAObjAnimeAll(HSD_JObj *joint)
{
    HSD_AObj *aobj;
    f32 frame;

    if (joint == 0)
        return 0;
    aobj = getAnimAobj(joint);
    if (aobj == 0)
        return 0;
    frame = HSD_AObjGetCurrFrame(aobj);
    HSD_JObjAnimAll(joint);
    if (!(sAObjGetFlags(aobj) & AOBJ_REWINDED))
        return 0;
    setAnimFrame(joint, frame);
    setAnimRate(joint, 0.0f);
    return 1;
}
