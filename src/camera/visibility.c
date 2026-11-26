#include "game_camera.h"
#include "game_pad.h"
#include "zoid.h"

extern s32 sCameraIn(CameraState *camera, HSD_JObj *joint);

s32 camZdLimit(CameraState *camera, ZoidState *zoid)
{
    s32 first, second, third, fourth, fifth;
    if (zoid == 0)
        return 1;
    if (zoid->joint == 0)
        return 1;
    if (camera == 0)
        return 1;
    first = sCameraIn(camera, zoid->joint);
    if (first == 0)
        return 0;
    second = sCameraIn(camera, zoid->joint);
    if (second == 0)
        return 0;
    third = sCameraIn(camera, zoid->head_base_joint);
    if (third == 0)
        return 0;
    fourth = sCameraIn(camera, zoid->hip_base_joint);
    if (fourth == 0)
        return 0;
    fifth = sCameraIn(camera, zoid->feet[2].joint);
    if (fifth == 0)
        return 0;
    if (sCameraIn(camera, zoid->tail_coobjs[0].joint) == 0)
        return 0;
    if (camera->pad != 0 && camera->pad->y != 0)
        return 2;
    if (first == 1)
        return 1;
    if (second == 1)
        return 1;
    if (third == 1)
        return 1;
    if (fourth == 1)
        return 1;
    if (fifth == 1)
        return 1;
    return 2;
}

s32 camZdLimit2(CameraState *camera, ZoidState *zoid)
{
    s32 result;
    if (zoid == 0)
        return 0;
    if (zoid->joint == 0)
        return 0;
    if (camera == 0)
        return 0;
    result = sCameraIn2(camera, zoid->joint);
    result |= sCameraIn2(camera, zoid->joint);
    result |= sCameraIn2(camera, zoid->head_base_joint);
    result |= sCameraIn2(camera, zoid->hip_base_joint);
    result |= sCameraIn2(camera, zoid->feet[2].joint);
    result |= sCameraIn2(camera, zoid->tail_coobjs[0].joint);
    return result;
}
