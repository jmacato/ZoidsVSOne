#include "zoid.h"

extern void stCopyMatRet(HSD_JObj *joint, JointPose *pose);

void ZoidCopyMatRet(ZoidState *zoid)
{
    stCopyMatRet(zoid->joint, zoid->pose);
}
