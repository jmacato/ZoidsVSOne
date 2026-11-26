#include "joint.h"

extern HSD_JObj *GetChild(void *archive, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void HSD_JObjDisp(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);

void ttlMenuDispParts(void *archive, s32 a, s32 b, s32 c, s32 d)
{
    HSD_JObj *joint;
    if (archive != 0) {
        joint = GetChild(archive, a, b, c, d, -1);
        if (joint != 0)
            HSD_JObjDisp(joint, 0, 7, 0);
    }
}
