#include "joint.h"

extern void ZoidLinerAnim(HSD_JObj *joint, JointPose *pose, f32 fraction);

void ZoidLinerAnimNext(HSD_JObj *joint, JointPose *pose, f32 fraction)
{
    while (joint != 0 && pose != 0) {
        ZoidLinerAnim(joint, pose, fraction);
        joint = joint->next;
        pose = pose->next;
    }
}
