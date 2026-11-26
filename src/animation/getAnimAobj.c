#include "joint.h"

#pragma dont_inline on

struct HSD_AObj *getAnimAobj(HSD_JObj *joint)
{
    struct HSD_AObj *animation;

    if (joint == 0) {
        return 0;
    }
    if (joint->animation != 0) {
        return joint->animation;
    }
    for (joint = joint->child; joint != 0; joint = joint->next) {
        animation = getAnimAobj(joint);
        if (animation != 0) {
            return animation;
        }
    }
    return 0;
}
