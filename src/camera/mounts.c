#include "game_camera.h"
#include "zoid.h"

#define offsetof(type, member) ((u32)&((type *)0)->member)

void camPara(CameraState *camera)
{
    ZoidState *zoid;
    s32 slot;

    if (camera == 0)
        return;
    zoid = camera->zoid;
    if (zoid == 0)
        return;
    slot = ((s32 *)zoid->control)[
        camera->mount_index * (sizeof(CameraMountInfo) / sizeof(s32))
        + offsetof(ZoidControlData, camera_mounts[0].joint_slot) / sizeof(s32)];
    if (zoid->weapon_slots[slot].joint == 0)
        return;
    camera->relative_origin.x = camera->mount_positions[camera->mount_index].x;
    camera->relative_origin.y = camera->mount_positions[camera->mount_index].y;
    camera->relative_origin.z = camera->mount_positions[camera->mount_index].z;
}

void camCockpit(CameraState *camera, ZoidState *zoid)
{
    HSD_JObj *joint;
    s32 axis;

    if (camera == 0)
        return;
    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    joint = zoid->weapon_slots[19].joint;
    if (joint == 0)
        return;
    for (axis = 0; axis < 3; axis++) {
        f32 translation = joint->matrix[axis][3];
        ((f32 *)&camera->eye)[axis] = translation;
        ((f32 *)&camera->interest)[axis] = translation + 10.0F * joint->matrix[axis][0];
    }
}
