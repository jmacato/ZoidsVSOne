#include "game_camera.h"
#include "cobj.h"

extern HSD_CameraDescPerspective cameraNormal;

void sCameraSetHalf(CameraState *camera, s32 first)
{
    Scissor firstScissor = {0, 320, 0, 480};
    Scissor secondScissor = {320, 640, 0, 480};
    HSD_RectS16 firstViewport = {0, 320, 0, 480};
    HSD_RectS16 secondViewport = {320, 640, 0, 480};
    if (camera != 0) {
        sCameraReset(camera);
        camera->cobj = HSD_CObjLoadDesc((HSD_CObjDesc *)&cameraNormal);
        HSD_CObjSetScissor(camera->cobj, first ? &firstScissor : &secondScissor);
        HSD_CObjSetViewport(camera->cobj, first ? &firstViewport : &secondViewport);
        HSD_CObjSetAspect(camera->cobj, 0.665F);
        camera->field_170 = 0;
        camera->zoid = 0;
        camera->mode = CAMERA_MODE_HALF;
        sCamNN = 2;
        sCamNS = 1;
        camera->half = first ? 0 : 1;
    }
}

void sCameraSetHalf2(CameraState *camera, s32 first)
{
    Scissor firstScissor = {0, 640, 0, 240};
    Scissor secondScissor = {0, 640, 240, 480};
    HSD_RectS16 firstViewport = {0, 640, 0, 240};
    HSD_RectS16 secondViewport = {0, 640, 240, 480};
    if (camera != 0) {
        sCameraReset(camera);
        camera->cobj = HSD_CObjLoadDesc((HSD_CObjDesc *)&cameraNormal);
        HSD_CObjSetScissor(camera->cobj, first ? &firstScissor : &secondScissor);
        HSD_CObjSetViewport(camera->cobj, first ? &firstViewport : &secondViewport);
        HSD_CObjSetAspect(camera->cobj, 2.66F);
        camera->field_170 = 0;
        camera->zoid = 0;
        camera->mode = CAMERA_MODE_HALF;
        sCamNN = 2;
        sCamNS = 0;
        camera->half = first ? 0 : 1;
    }
}

