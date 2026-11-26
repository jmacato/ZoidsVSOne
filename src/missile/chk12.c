#include "zoid_collision.h"

extern f32 sLenJobj(HSD_JObj *joint, HSD_JObj *target);

s32 chk12(CoObj *object, HSD_JObj *target, f32 range)
{
    HSD_JObj *joint;
    if (object == 0)
        return 0;
    joint = object->joint;
    if (joint == 0)
        return 0;
    if (target == 0)
        return 0;
    if (sLenJobj(joint, target) > range + object->minimum_scale)
        return 0;
    return 1;
}
