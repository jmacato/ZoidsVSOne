#include "game_camera.h"
#include "zoid.h"

extern f32 cosf(f32 angle);
extern f32 sinf(f32 angle);

void sCameraTargetZoid(CameraState *camera, ZoidState *zoid)
{
    HSD_JObj *joint;
    if (camera != 0 && zoid != 0) {
        camera->zoid = zoid;
        joint = 0;
        camera->target_index = zoid->index;
        zoid->camera = camera;
        if (zoid->body_coobj.joint != 0)
            joint = zoid->body_coobj.joint;
        else if (zoid->head_coobj.joint != 0)
            joint = zoid->head_coobj.joint;
        else if (zoid->neck_coobj.joint != 0)
            joint = zoid->neck_coobj.joint;
        else if (zoid->hip_coobj.joint != 0)
            joint = zoid->hip_coobj.joint;
        else if (zoid->tail_coobjs[0].joint != 0)
            joint = zoid->tail_coobjs[0].joint;
        camera->field_170 = joint;
    }
}

void sCameraRela(CameraState *camera, Vec3 *position, Vec3 *relative)
{
    f32 cosine = cosf(camera->yaw);
    f32 angle = camera->yaw;
    f32 sine = sinf(angle);
    if (camera->zoid != 0 && camera->zoid->joint != 0) {
        f32 inputX = position->x;
        f32 inputZ = position->z;
        Vec3 delta;
        delta.z = inputZ - camera->relative_origin.z;
        delta.x = inputX - camera->relative_origin.x;
        relative->x = -delta.x * cosine + delta.z * sine;
        relative->z = delta.x * sine + delta.z * cosine;
    }
}
