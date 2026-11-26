#include "zoid.h"

void zdGetBodyPt(ZoidState *zoid, Vec3 *point)
{
    HSD_JObj *joint;

    point->x = zoid->position[0];
    point->y = zoid->position[1];
    point->z = zoid->position[2];
    joint = zoid->buckle_joint;
    if (joint == 0) {
        joint = zoid->bust_base_joint;
    }
    if (joint == 0) {
        joint = zoid->hip_base_joint;
    }
    if (joint == 0) {
        joint = zoid->body_coobj.joint;
    }
    if (joint == 0) {
        joint = zoid->bust_coobj.joint;
    }
    if (joint == 0) {
        return;
    }
    point->x = joint->matrix[0][3];
    point->y = joint->matrix[1][3];
    point->z = joint->matrix[2][3];
}
