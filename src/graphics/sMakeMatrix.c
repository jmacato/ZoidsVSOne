#pragma inline_depth(2)
#include "joint_matrix.h"

#pragma auto_inline off
void sMakeMatrix(HSD_JObj *joint)
{
    if (joint != 0) {
        setup_matrix(joint);
        for (joint = joint->child; joint != 0; joint = joint->next)
            sMakeMatrix(joint);
    }
}
