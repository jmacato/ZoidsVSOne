#include "joint.h"

extern struct HSD_AObj *getAnimAobj(HSD_JObj *joint);

struct HSD_AObj *getAnimAobjXor(HSD_JObj *joint, HSD_JObj *excluded)
{
    struct HSD_AObj *animation;

    if (joint == excluded) {
        return 0;
    }
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
