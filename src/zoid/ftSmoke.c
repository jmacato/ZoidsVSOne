#include "zoid.h"
#include "missile.h"

void ftSmoke(ZoidState *zoid, FootJoint *foot, s32 frame)
{
    HSD_JObj *joint;
    u32 flags;

    if (zoid == 0) {
        return;
    }
    if (foot == 0) {
        return;
    }
    joint = foot->joint;
    if (joint == 0) {
        return;
    }
    flags = foot->flags;
    if ((flags & FOOT_FLAG_CONTACT) && !(flags & FOOT_FLAG_PREVIOUS_CONTACT) && frame > 3) {
        sEffectSet(56, 1, 0, joint, 0);
    }
    foot->flags = (flags & FOOT_FLAG_CONTACT) ? (flags | FOOT_FLAG_PREVIOUS_CONTACT) : (flags & ~FOOT_FLAG_PREVIOUS_CONTACT);
}
