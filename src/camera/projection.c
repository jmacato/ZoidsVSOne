#include "game_camera.h"
#include "cobj.h"
#include "joint.h"

typedef struct ScreenPoint {
    f32 x, y;
} ScreenPoint;

typedef struct CameraBounds {
    s32 xmin, xmax, ymin, ymax;
} CameraBounds;

HSD_WObjDesc camNormal_pos_wobjdesc = {0, {20.0F, 20.0F, 20.0F}, 0};
HSD_WObjDesc camNormal_interest_wobjdesc = {0, {0.0F, 0.0F, 0.0F}, 0};
HSD_CameraDescPerspective cameraNormal = {
    0, 0, 1, {0, 640, 0, 480}, {0, 640, 0, 480},
    &camNormal_pos_wobjdesc, &camNormal_interest_wobjdesc,
    0.0F, 0, 1.1F, 14000.0F, 60.0F, 1.33F
};
/* 1: single view, 2a/2b: top/bottom half views (sCamNS 0), 3a/3b: left/right half views (sCamNS 1) */
CameraBounds sctblMin1a = {50, 590, 50, 400};
CameraBounds sctblMin2a = {50, 590, 25, 190};
CameraBounds sctblMin2b = {50, 590, 265, 440};
CameraBounds sctblMin3a = {5, 315, 50, 400};
CameraBounds sctblMin3b = {325, 635, 50, 400};
CameraBounds sctblMax1a = {130, 400, 100, 360};
CameraBounds sctblMax2a = {130, 400, 50, 170};
CameraBounds sctblMax2b = {130, 400, 290, 420};
CameraBounds sctblMax3a = {25, 305, 100, 360};
CameraBounds sctblMax3b = {335, 625, 100, 360};

s32 sCameraIn2(CameraState *camera, HSD_JObj *joint)
{
    f32 depth;
    ScreenPoint screen;
    Vec3 world;
    s32 x, y;
    CameraBounds *outer;
    CameraBounds *inner;
    if (joint == 0)
        return 0;
    world.x = joint->matrix[0][3];
    world.y = joint->matrix[1][3];
    world.z = joint->matrix[2][3];
    GXProject(world.x, world.y, world.z,
              camera->view, camera->projection, camera->viewport,
              &screen.x, &screen.y, &depth);
    x = screen.x;
    y = screen.y;
    if (depth >= 1.0)
        return 0;
    outer = &sctblMin1a;
    inner = &sctblMax1a;
    if (sCamNN == 2) {
        if (sCamNS == 0) {
            if (camera->half == 0) {
                outer = &sctblMin2a;
                inner = &sctblMax2a;
            } else {
                outer = &sctblMin2b;
                inner = &sctblMax2b;
            }
        } else {
            if (camera->half == 0) {
                outer = &sctblMin3a;
                inner = &sctblMax3a;
            } else {
                outer = &sctblMin3b;
                inner = &sctblMax3b;
            }
        }
    }
    if (x < outer->xmin)
        return CAMERA_OUT_LEFT;
    if (x > outer->xmax)
        return CAMERA_OUT_RIGHT;
    if (y < outer->ymin)
        return CAMERA_OUT_TOP;
    if (y > outer->ymax)
        return CAMERA_OUT_BOTTOM;
    if (x > inner->xmin && x < inner->xmax && y > inner->ymin && y < inner->ymax)
        return CAMERA_IN_CENTER;
    return 0;
}

s32 sCameraPt2d(CameraState *camera, Vec3 *position, s32 *screen_point)
{
    f32 depth;
    ScreenPoint screen;
    GXProject(position->x, position->y, position->z,
              camera->view, camera->projection, camera->viewport,
              &screen.x, &screen.y, &depth);
    screen_point[0] = screen.x;
    screen_point[1] = screen.y;
    if (depth < 1.0)
        return 1;
    return 0;
}

s32 sCameraJobjPt2d(CameraState *camera, HSD_JObj *joint, s32 *screen_point)
{
    f32 depth;
    ScreenPoint screen;
    GXProject(joint->matrix[0][3], joint->matrix[1][3], joint->matrix[2][3],
              camera->view, camera->projection, camera->viewport,
              &screen.x, &screen.y, &depth);
    screen_point[0] = screen.x;
    screen_point[1] = screen.y;
    if (depth < 1.0)
        return 1;
    return 0;
}
