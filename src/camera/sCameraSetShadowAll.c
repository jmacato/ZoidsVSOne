#include "game_camera.h"

extern void sCameraSetShadow(CameraState *camera);

void sCameraSetShadowAll(void)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        sCameraSetShadow(&sCamera[i]);
    }
}
