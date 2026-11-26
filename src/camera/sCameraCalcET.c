#include "game_camera.h"
#include "zoid.h"

#define offsetof(type, member) ((u32)&((type *)0)->member)

extern f64 __frsqrte(f64);
extern f32 atan2f(f32 y, f32 x);
extern f32 acosf(f32 x);
extern f32 sLenPoint3dR(Vec3 *point);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

void sCameraCalcET(CameraState *camera)
{
    ZoidState *zoid;
    HSD_JObj *joint;
    f32 planar;
    f32 length;
    s32 unused[3];
    volatile f32 root;
    s32 unused2[2];
    f32 z;
    f32 x;

    if (camera != 0 && camera->cobj != 0 && (zoid = camera->zoid) != 0) {
        joint = zoid->weapon_slots[((s32 *)zoid->control)[
            camera->mount_index * (sizeof(CameraMountInfo) / sizeof(s32))
            + offsetof(ZoidControlData, camera_mounts[0].joint_slot) / sizeof(s32)]].joint;
        if (joint != 0) {
            camera->direction.x = camera->focus.x - joint->matrix[0][3];
            camera->direction.y = camera->focus.y - joint->matrix[1][3];
            camera->direction.z = camera->focus.z - joint->matrix[2][3];
            z = camera->direction.z;
            x = camera->direction.x;
            planar = sqrtf(z * z + x * x, &root);
            length = sLenPoint3dR(&camera->direction);
            if (0.0f != length) {
                camera->focus_elevation = acosf(planar / length);
                camera->focus_heading = atan2f(x, z);
            }
        }
    }
}
