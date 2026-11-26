#include "game_camera.h"

extern s32 nowShadow;
extern CameraState *camTmp;
extern void shadowRendering(struct HSD_Shadow *shadow, s32 index);

void sCameraShadowAll(void)
{
    CameraState *camera;
    s32 i;

    if (nowShadow == 0) {
        for (i = 0; i < 4; i++) {
            camera = &sCamera[i];
            camTmp = camera;
            if (camera->cobj != 0 && camera->lights != 0 && camera->shadow != 0) {
                shadowRendering(camera->shadow, camera->target_index);
            }
        }
    }
}
