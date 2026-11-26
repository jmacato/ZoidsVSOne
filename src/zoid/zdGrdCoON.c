#include "zoid.h"

extern f32 zdColPosY(Vec3 *point, u16 *selector);

void zdGrdCoON(ZoidState *zoid, CoObj *co, s32 flag)
{
    u16 selector;
    Vec3 position;
    Vec3 frame_padding;
    f32 depth;

    if (co != 0 && co->joint != 0) {
        position.x = co->joint->matrix[0][3];
        position.y = co->joint->matrix[1][3];
        position.z = co->joint->matrix[2][3];
        depth = co->ground_y = zdColPosY(&position, &selector);
        depth -= position.y;
        if (depth >= 0.0f) {
            zoid->grounded = 1;
            if (zoid->max_ground_depth < depth) {
                zoid->max_ground_depth = depth;
            }
        }
        if (flag != 0 && *(void **)&co->ground_contact != 0) {
            zoid->grounded = 1;
        }
    }
}
