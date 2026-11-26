#include "joint.h"

extern struct HSD_AObj *getAnimAobj(HSD_JObj *joint);
extern s32 getEndF(HSD_JObj *joint);

s32 getEndFA(HSD_JObj *joint)
{
    if (joint == 0) {
        return 1;
    }
    if (getAnimAobj(joint) == 0) {
        return 1;
    }
    return getEndF(joint);
}
