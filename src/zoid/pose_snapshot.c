#include "zoid.h"

#define JOBJ_INSTANCE 0x1000

#pragma dont_inline on

JointPose *zdSearchBAK(HSD_JObj *joint, JointPose *pose, HSD_JObj *target)
{
    JointPose *found;
    if (joint == 0)
        return 0;
    if (pose == 0)
        return 0;
    if (joint == target)
        return pose;
    joint = joint ? joint->child : 0;
    pose = pose ? pose->child : 0;
    while (joint != 0) {
        found = zdSearchBAK(joint, pose, target);
        if (found != 0)
            return found;
        joint = joint ? joint->next : 0;
        pose = pose ? pose->next : 0;
    }
    return 0;
}

void ZoidCopyAnim1(HSD_JObj *joint, JointPose *pose)
{
    s32 row, column;
    if (joint != 0 && pose != 0) {
        pose->rotation[0] = joint->rotation[0];
        pose->rotation[1] = joint->rotation[1];
        pose->rotation[2] = joint->rotation[2];
        pose->translation.x = joint->translation.x;
        pose->translation.y = joint->translation.y;
        pose->translation.z = joint->translation.z;
        pose->scale.x = joint->scale.x;
        pose->scale.y = joint->scale.y;
        pose->scale.z = joint->scale.z;
        for (row = 0; row < 3; row++) {
            for (column = 0; column < 4; column++) {
                pose->matrix[row][column] = joint->matrix[row][column];
            }
        }
        if ((joint->flags & JOBJ_INSTANCE) != 0)
            return;
        joint = joint->child;
        pose = pose->child;
        while (joint != 0) {
            if (joint == 0 || pose == 0)
                return;
            ZoidCopyAnim1(joint, pose);
            joint = joint->next;
            pose = pose->next;
        }
    }
}

void zdLinierReset(ZoidState *zoid, HSD_JObj *joint)
{
    JointPose *pose;
    if (joint != 0) {
        pose = zoid->pose;
        pose = zdSearchBAK(zoid->joint, pose, joint);
        if (pose != 0)
            ZoidCopyAnim1(joint, pose);
    }
}

extern HSD_JObj *jobjWithAobj(HSD_JObj *joint);
extern JointPose *stSearchJobj(HSD_JObj *joint, JointPose *pose, HSD_JObj *target);
s32 zdGetAnimNum(ZoidState *zoid, HSD_JObj *joint)
{
    JointPose *pose;
    joint = jobjWithAobj(joint);
    pose = stSearchJobj(zoid->joint, zoid->pose, joint);
    if (pose == 0)
        return -1;
    return pose->animation_index;
}
