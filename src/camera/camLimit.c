#include "zoid.h"
#include "game_camera.h"

extern s32 sctblNrm1a;

void camLimit(CameraState *camera)
{
    s32 frame_padding[1];
    ZoidState *zoid;
    ZoidState *target;
    s32 zoid_flags;
    s32 zoid_below;
    s32 target_flags;
    s32 point[2];
    s32 pad[1];
    f32 middle;

    if (camera != 0 && (zoid = camera->zoid, camera->zoid != 0) && zoid->joint != 0) {
        camZdLimit(camera, zoid);
        zoid_flags = camZdLimit2(camera, zoid);
        target = 0;
        if (zoid->target_pending != 0) {
            target = &Zoid[zoid->target_slot];
            if (target != 0 && target->joint == 0) {
                target = 0;
            }
        }
        target_flags = camZdLimit2(camera, target);
        zoid_below = zoid_flags & CAMERA_OUT_BOTTOM;
        if (zoid_below == 0 && zoid->target_pending != 0) {
            if ((target_flags & (CAMERA_OUT_TOP | CAMERA_OUT_BOTTOM)) == CAMERA_OUT_TOP) {
                camera->focus_y_offset += 1.09;
            }
            if ((target_flags & (CAMERA_OUT_TOP | CAMERA_OUT_BOTTOM)) == CAMERA_OUT_BOTTOM) {
                camera->focus_y_offset -= 1.05;
            }
            if ((target_flags & (CAMERA_OUT_TOP | CAMERA_OUT_LEFT | CAMERA_OUT_BOTTOM | CAMERA_OUT_RIGHT)) == 0 && target != 0) {
                middle = sctblNrm1a;
                if (sCamNN == 2 && sCamNS == 0) {
                    middle = sctblNrm1a / 2 + camera->half * 240;
                }
                if (sCameraJobjPt2d(camera, target->camera_joint, point) != 0) {
                    if ((f32)point[1] < middle) {
                        camera->focus_y_offset += 0.1;
                    } else {
                        camera->focus_y_offset -= 0.1;
                    }
                }
            }
        }
        if (camera->focus_y_offset > 100.0f) {
            camera->focus_y_offset = 100.0f;
        }
        if (camera->focus_y_offset < -100.0f) {
            camera->focus_y_offset = -100.0f;
        }
        if (zoid_below == 0) {
            if (camera->focus_distance > 100.0f) {
                camera->focus_distance -= 0.01;
                if (camera->focus_distance < 100.0f) {
                    camera->focus_distance = 100.0f;
                }
            }
            if (camera->focus_distance < 100.0f) {
                camera->focus_distance += 0.01;
                if (camera->focus_distance > 100.0f) {
                    camera->focus_distance = 100.0f;
                }
            }
        }
        if (zoid_below != 0) {
            if (camera->focus_distance > 100.0f) {
                camera->focus_distance -= 1.0f;
            }
            if (camera->focus_distance > 70.0f) {
                camera->focus_distance -= 1.0f;
            }
            if (camera->focus_distance > 50.0f) {
                camera->focus_distance -= 1.0f;
            }
            if (camera->focus_distance > 20.0f) {
                camera->focus_distance -= 1.0f;
            }
            camera->focus_distance -= 1.0f;
        }
        if (zoid_flags & CAMERA_OUT_TOP) {
            camera->focus_distance += 0.1;
        }
        if (zoid->target_pending != 0) {
            if (camera->focus_distance < 0.3) {
                camera->focus_distance = 0.3f;
            }
        } else if (camera->focus_distance < 1.0f) {
            camera->focus_distance = 1.0f;
        }
        if (camera->focus_distance > 150.0f) {
            camera->focus_distance = 150.0f;
        }
    }
}
