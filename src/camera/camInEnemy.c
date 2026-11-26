#include "game_camera.h"
#include "zoid.h"

extern f32 sPassage(Vec3 *start, Vec3 *end, Vec3 *point);

static inline f32 camPass(Vec3 *start, Vec3 *end, Vec3 *point)
{
    f32 d = sPassage(start, end, point);
    return d;
}

void camInEnemy(CameraState *camera, ZoidState *zoid)
{
    ZoidState *target;
    s32 i;
    ZoidControlData *control;
    s32 blocked;
    Vec3 mine;
    Vec3 enemy;

    if (zoid == 0) {
        return;
    }
    control = zoid->control;
    if (zoid->target_pending != 0) {
        target = &Zoid[zoid->target_slot];
        if (target != 0 && target->joint == 0) {
            return;
        }
        mine.x = zoid->camera_joint->matrix[0][3];
        enemy.x = target->camera_joint->matrix[0][3];
        mine.y = zoid->camera_joint->matrix[1][3];
        enemy.y = target->camera_joint->matrix[1][3];
        mine.z = zoid->camera_joint->matrix[2][3];
        enemy.z = target->camera_joint->matrix[2][3];
        for (i = 0; i < 20; i++) {
            if (zoid->weapon_slots[control->camera_mounts[i].joint_slot].joint == 0) {
                camera->mount_hidden[i] = 1;
                camera->mount_blocked[i] = 1;
            } else {
                blocked = 0;
                if (camPass(&camera->mount_positions[i], &mine, &enemy) < target->body_coobj.minimum_scale / 3.0f) {
                    blocked = 1;
                } else if (camPass(&camera->mount_positions[i], &enemy, &mine) < zoid->body_coobj.minimum_scale / 3.0f) {
                    blocked = 1;
                }
                camera->mount_blocked[i] = blocked;
            }
        }
    }
}
