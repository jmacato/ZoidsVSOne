#include "jobj.h"

extern u32 HSD_AObjGetFlags(HSD_AObj *animation);

#pragma dont_inline on
s32 getEndF1(HSD_JObj *joint)
{
    if (joint == 0)
        return 1;
    if (joint->animation != 0) {
        u32 flags = HSD_AObjGetFlags(joint->animation);
        if (flags & AOBJ_REWINDED)
            return 1;
        if (flags & AOBJ_NO_ANIM)
            return 1;
        return 0;
    }
    return 1;
}

s32 getEndF(HSD_JObj *joint)
{
    if (joint == 0)
        return 1;
    if (joint->animation != 0) {
        u32 flags = HSD_AObjGetFlags(joint->animation);
        if (flags & AOBJ_REWINDED)
            return 1;
        if (flags & AOBJ_NO_ANIM)
            return 1;
        return 0;
    }
    for (joint = joint->child; joint != 0; joint = joint->next) {
        if (getEndF(joint) != 0)
            return 1;
    }
    return 0;
}

s32 jobjAnim(HSD_JObj *joint)
{
    if (joint == 0)
        return 0;
    HSD_JObjAnimAll(joint);
    return getEndF(joint);
}

s32 jobjAnim1(HSD_JObj *joint)
{
    if (joint == 0)
        return 0;
    HSD_JObjAnim(joint);
    return getEndF(joint);
}
