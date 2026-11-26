#include "zoid.h"

void zdAddAnimRy(ZoidState *zoid)
{
    HSD_JObj *joint;

    if (zoid != 0) {
        joint = zoid->joint;
        if (joint != 0 && joint->child != 0) {
            zoid->position[0] = zoid->child_matrix[0][3];
            zoid->position[1] = zoid->child_matrix[1][3];
            zoid->position[2] = zoid->child_matrix[2][3];
            zoid->heading += zoid->heading_delta;
            zoid->height_offset = 0.0f;
        }
    }
}
