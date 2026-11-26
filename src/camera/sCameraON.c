#include "zoid.h"
#include "game_camera.h"
#include "ground_collision.h"

#define CAMERA_MOUNT_COCKPIT 20

extern void camInMine(CameraState *camera, ZoidState *zoid);
extern void camInEnemy(CameraState *camera, ZoidState *zoid);
extern void setCamTgtLockOFF(CameraState *camera);
extern void sCameraCalcET(CameraState *camera);
extern void angLimit(f32 *angle);
extern void camLimit(CameraState *camera);
extern void sCamBallOut(CameraState *camera, f32 radius);
extern void linierCamXZ(CameraState *camera, s32 mode);
extern void HSD_CObjSetInterest(struct HSD_CObj *cobj, Vec3 *interest);
extern void HSD_CObjSetEyePosition(struct HSD_CObj *cobj, Vec3 *position);
extern void sCameraCalc(CameraState *camera);

void sCameraON(CameraState *camera)
{
    s32 frame_padding[3];
    GroundMask mask = {{0, 255, 0, 0}};
    ZoidState *zoid;
    s32 mount;
    s32 n;
    s32 pad[2];

    if (camera != 0 && camera->cobj != 0 && (zoid = camera->zoid, camera->zoid != 0)) {
        camInMine(camera, zoid);
        camera->mount_timer++;
        mount = camera->mount_index;
        if (mount == CAMERA_MOUNT_COCKPIT) {
            mount = 0;
        }
        if (camera->mount_timer > 300) {
            if (zoid->target_pending != 0) {
                if (mount != 10 && camera->mount_hidden[10] == 0 && camera->mount_blocked[10] == 0) {
                    camera->mount_timer = 0;
                    camera->mount_index = 10;
                    camera->focus_distance = 100.0f;
                    camera->focus_y_offset = 0.0f;
                }
            } else if (mount != 0 && camera->mount_hidden[0] == 0) {
                camera->mount_timer = 0;
                camera->mount_index = 0;
                camera->focus_distance = 100.0f;
                camera->focus_y_offset = 0.0f;
            }
        }
        if (mount != CAMERA_MOUNT_COCKPIT) {
        if (camera->mount_hidden[mount] != 0) {
            for (n = 0; n < 20; n++, mount++) {
                if (mount >= 20) {
                    mount = 0;
                }
                if (zoid->target_pending == 0) {
                    mount = mount % 10;
                } else {
                    mount = mount % 10 + 10;
                }
                if (camera->mount_hidden[mount] == 0 && (zoid->target_pending == 0 || camera->mount_blocked[mount] == 0)) {
                    camera->mount_timer = 0;
                    camera->mount_index = mount;
                    camera->focus_distance = 100.0f;
                    camera->focus_y_offset = 0.0f;
                    break;
                }
            }
        }
        if (camera->mount_timer > 120 && zoid->target_pending != 0) {
            camInEnemy(camera, zoid);
            if (mount != CAMERA_MOUNT_COCKPIT && camera->mount_blocked[mount] != 0) {
                for (n = 0; n < 20; n++) {
                    if (mount >= 20) {
                        mount = 10;
                    }
                    if (camera->mount_hidden[mount] == 0 && camera->mount_blocked[mount] == 0) {
                        camera->mount_timer = 0;
                        camera->mount_index = mount;
                        camera->focus_distance = 100.0f;
                        camera->focus_y_offset = 0.0f;
                        break;
                    }
                    mount++;
                }
            }
        }
        }
        if (camera->zoid != 0 && camera->zoid->target_pending != 0) {
            setCamTgtLockON(camera);
            sCameraCalcET(camera);
        } else {
            setCamTgtLockOFF(camera);
        }
        angLimit(&camera->focus_heading);
        camPara(camera);
        camLimit(camera);
        if (camera->linier_timer != 0) {
            camera->linier_timer--;
        }
        sCamBallOut(camera, 20.0f);
        sColBallYH(&camera->relative_origin, &mask, GROUND_BALL_PUSH_OUT, 8.0f);
        if (linierCamLimitXZ(camera, 5.0f) != 0) {
            camera->linier_timer = 180;
        }
        if (camera->linier_timer != 0) {
            linierCamXZ(camera, 1);
        }
        if (mount == CAMERA_MOUNT_COCKPIT) {
            camCockpit(camera, camera->zoid);
        }
        HSD_CObjSetInterest(camera->cobj, &camera->interest);
        HSD_CObjSetEyePosition(camera->cobj, &camera->eye);
        sCameraCalc(camera);
        camera->saved_eye.x = camera->eye.x;
        camera->saved_interest.x = camera->interest.x;
        camera->saved_eye.y = camera->eye.y;
        camera->saved_interest.y = camera->interest.y;
        camera->saved_eye.z = camera->eye.z;
        camera->saved_interest.z = camera->interest.z;
    }
}
