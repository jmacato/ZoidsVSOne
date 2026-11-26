#include "zoid.h"
#include "game_camera.h"
#include "lobj.h"

extern struct HSD_Shadow *makeShadow(HSD_LObj *light);
extern void HSD_ShadowAddObject(struct HSD_Shadow *shadow, HSD_JObj *jobj);
extern void HSD_ShadowSetActive(struct HSD_Shadow *shadow, int active);

void sCameraSetShadow(CameraState *camera)
{
    HSD_LObj *light;

    if (camera != 0 && camera->cobj != 0) {
        light = camera->lights;
        while (light != 0) {
            if ((light->flags & LOBJ_TYPE_MASK) != LOBJ_AMBIENT) {
                camera->shadow = makeShadow(light);
                HSD_ShadowAddObject(camera->shadow, camera->zoid->joint);
                HSD_ShadowSetActive(camera->shadow, 0);
                break;
            }
            if (light == 0)
                light = 0;
            else
                light = light->next;
        }
    }
}
