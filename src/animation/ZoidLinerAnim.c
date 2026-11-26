#include "joint.h"

#define JOBJ_INSTANCE 0x1000

#pragma dont_inline on

extern f32 sLiner(f32 target, f32 current, f32 fraction);

void ZoidLinerAnim(HSD_JObj *joint, JointPose *pose, f32 fraction)
{
    s32 row;
    s32 column;

    if (joint != 0 && pose != 0) {
        joint->translation.x = sLiner(joint->translation.x, pose->translation.x, fraction);
        joint->translation.y = sLiner(joint->translation.y, pose->translation.y, fraction);
        joint->translation.z = sLiner(joint->translation.z, pose->translation.z, fraction);
        joint->rotation[0] = sLiner(joint->rotation[0], pose->rotation[0], fraction);
        joint->rotation[1] = sLiner(joint->rotation[1], pose->rotation[1], fraction);
        joint->rotation[2] = sLiner(joint->rotation[2], pose->rotation[2], fraction);
        joint->scale.x = sLiner(joint->scale.x, pose->scale.x, fraction);
        joint->scale.y = sLiner(joint->scale.y, pose->scale.y, fraction);
        joint->scale.z = sLiner(joint->scale.z, pose->scale.z, fraction);
        for (row = 0; row < 3; row++) {
            for (column = 0; column < 4; column++) {
                joint->matrix[row][column] = sLiner(joint->matrix[row][column],
                                                   pose->matrix[row][column], fraction);
            }
        }
        if ((joint->flags & JOBJ_INSTANCE) != 0) {
            return;
        }
        joint = joint->child;
        pose = pose->child;
        while (joint != 0) {
            if (joint == 0 || pose == 0) {
                return;
            }
            ZoidLinerAnim(joint, pose, fraction);
            joint = joint->next;
            pose = pose->next;
        }
    }
}
