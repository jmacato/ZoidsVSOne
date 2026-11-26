#include "zoid_collision.h"

#define JOBJ_HIDDEN 0x10

extern void HSD_JObjSetFlags(HSD_JObj *joint, u32 flags);

void zdCoObjOFF(CoObj *object)
{
    HSD_JObj *joint;
    if (object != 0) {
        joint = object->joint;
        if (joint != 0)
            HSD_JObjSetFlags(joint, JOBJ_HIDDEN);
    }
}
