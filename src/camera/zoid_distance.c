#include "game_camera.h"
#include "zoid.h"
#include "matrix.h"

void sCameraLenZoid(CameraState *camera)
{
    s32 i;
    s32 axis;

    for (i = 0; i < 16; i++) {
        ZoidState *zoid = &Zoid[i];
        camera->zoid_distance[i] = 1000000000.0F;
        if (zoid->joint != 0) {
            Vec3 delta;
            for (axis = 0; axis < 3; axis++)
                ((f32 *)&delta)[axis] = ((f32 *)&camera->eye)[axis] - zoid->camera_joint->matrix[axis][3];
            camera->zoid_distance[i] = PSVECMag(&delta);
        }
    }
}
