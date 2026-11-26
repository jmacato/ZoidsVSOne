#include "game_camera.h"
#include "zoid.h"

#define offsetof(type, member) ((u32)&((type *)0)->member)

void setCamTgtLockON(CameraState *camera)
{
    HSD_JObj *joint;
    ZoidState *enemy;
    f32 enemy_weight, joint_weight;
    if (camera != 0 && camera->zoid != 0 && camera->zoid->joint != 0) {
        s32 slot = ((s32 *)camera->zoid->control)[
            camera->mount_index * (sizeof(CameraMountInfo) / sizeof(s32))
            + offsetof(ZoidControlData, camera_mounts[0].joint_slot) / sizeof(s32)];
        joint = camera->zoid->weapon_slots[slot].joint;
        if (joint != 0) {
            enemy = &Zoid[camera->zoid->target_slot];
            if (enemy == 0) {
                camera->zoid->target_pending = 0;
                return;
            }
            enemy_weight = camera->focus_distance / 150.0;
            joint_weight = 1.0F - enemy_weight;
            camera->focus.x = enemy->camera_joint->matrix[0][3] * enemy_weight + joint->matrix[0][3] * joint_weight;
            camera->focus.y = enemy->camera_joint->matrix[1][3] * enemy_weight + joint->matrix[1][3] * joint_weight;
            camera->focus.z = enemy->camera_joint->matrix[2][3] * enemy_weight + joint->matrix[2][3] * joint_weight;
            camera->focus.y += camera->focus_y_offset;
        }
    }
}
