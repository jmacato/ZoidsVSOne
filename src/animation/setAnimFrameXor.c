#include "joint.h"

#pragma dont_inline on

extern void HSD_AObjSetCurrentFrame(struct HSD_AObj *animation, f32 value);

void setAnimFrameXor(HSD_JObj *joint, HSD_JObj *excluded, f32 value)
{
    if (joint != 0 && joint != excluded) {
        if (joint->animation != 0) {
            HSD_AObjSetCurrentFrame(joint->animation, value);
        }
        for (joint = joint->child; joint != 0; joint = joint->next) {
            setAnimFrameXor(joint, excluded, value);
        }
    }
}
