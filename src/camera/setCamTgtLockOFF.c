#include "game_camera.h"
#include "zoid.h"

#define offsetof(type, member) ((u32)&((type *)0)->member)

extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

static inline f32 wcosf(f32 x)
{
    return cosf(x);
}

void setCamTgtLockOFF(CameraState *camera)
{
    HSD_JObj *joint;
    s32 frame_padding[1];
    f32 angle;
    s32 unused1[1];
    Vec3 position;
    s32 unused2[6];
    f32 distance;
    Vec3 *pos = &position;

    if (camera != 0 && camera->zoid != 0 && camera->zoid->joint != 0) {
        s32 slot = ((s32 *)camera->zoid->control)[
            camera->mount_index * (sizeof(CameraMountInfo) / sizeof(s32))
            + offsetof(ZoidControlData, camera_mounts[0].joint_slot) / sizeof(s32)];
        joint = camera->zoid->weapon_slots[slot].joint;
        if (joint != 0) {
            angle = camera->zoid->heading;
            distance = camera->focus_distance;
            camera->focus_heading = angle;
            angLimit(&angle);
            position.x = joint->matrix[0][3];
            position.y = joint->matrix[1][3];
            position.z = joint->matrix[2][3];
            position.x += distance * sinf(angle);
            position.z += distance * wcosf(angle);
            position.y += 2.0f;
            camera->focus.x = pos->x;
            camera->focus.y = pos->y;
            camera->focus.z = pos->z;
        }
    }
}
