#include "cobj.h"
#include "shadow.h"
#include "game_camera.h"
#include "game_pad.h"
#include "angle.h"

extern HSD_CameraDescPerspective cameraNormal;
extern void ZeroMemory(void *address, u32 length);

static inline s32 decrement_reference(void *object)
{
    s32 result;
    u16 *count = &((HSD_Obj *)object)->reference_count;
    if ((result = (*count == (u16)-1)))
        return result;
    return (*count)-- == 0;
}

static inline void HSD_CObjUnref(HSD_CObj *object)
{
    if (object != 0 && decrement_reference(object)) {
        if (object != 0) {
            object->parent.parent.class_info->release((HSD_Class *)object);
            object->parent.parent.class_info->destroy((HSD_Class *)object);
        }
    }
}

void sCameraInit(void)
{
    s32 i;
    sCamNormal = HSD_CObjLoadDesc((HSD_CObjDesc *)&cameraNormal);
    for (i = 0; i < 4; i++) {
        ZeroMemory(&sCamera[i], sizeof(CameraState));
        sCamera[i].pad = &sPad[i];
        sCamera[i].field_164 = 3;
        sCamera[i].focus_y_offset = 0.0F;
        sCamera[i].focus_heading = 0.0F;
        sCamera[i].field_018 = DEG2RAD_D(15.0F);
        sCamera[i].focus_elevation = 0.0F;
    }
}

void sCameraSetNormal(CameraState *camera)
{
    if (camera != 0) {
        sCameraReset(camera);
        camera->cobj = HSD_CObjLoadDesc((HSD_CObjDesc *)&cameraNormal);
        camera->field_170 = 0;
        camera->zoid = 0;
        camera->mode = CAMERA_MODE_NORMAL;
        sCamNN = 1;
        sCamNS = 0;
        camera->half = 0;
    }
}

void sCameraUn(void)
{
    s32 i;
    for (i = 0; i < 4; i++)
        sCameraReset(&sCamera[i]);
    if (sCamNormal != 0)
        HSD_CObjUnref(sCamNormal);
    sCamNormal = 0;
}

void sCameraPurge(void)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        CameraState *camera = &sCamera[i];
        sCameraReset(camera);
    }
}

void sCameraReset(CameraState *camera)
{
    if (camera != 0) {
        if (camera->shadow != 0) {
            HSD_ShadowRemove(camera->shadow);
            camera->shadow = 0;
        }
        if (camera->cobj != 0) {
            HSD_CObjUnref(camera->cobj);
            camera->cobj = 0;
        }
        camera->field_170 = 0;
        camera->focus_distance = 100.0F;
        camera->field_01C = 0.0F;
        camera->focus_heading = 0.0F;
        camera->field_018 = DEG2RAD_D(10.0F);
        camera->focus_y_offset = 0.0F;
    }
}

