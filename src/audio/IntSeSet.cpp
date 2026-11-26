extern "C" {
#include "game_camera.h"
#include "int_se.h"

extern s32 TEA_SeOn(s16 se, s32 x, s32 z);

#pragma force_active on
CameraState sCamera[4];
static IntSeEntry IntSe[12];
#pragma force_active off

s32 IntSeSet(s16 se, f32 distance, f32 x, f32 z)
{
    s32 i;

    for (i = 0; i < 12; i++) {
        if (IntSe[i].se != 0 && se == IntSe[i].se && IntSe[i].distance <= distance / 2.0f)
            return 0;
    }
    for (i = 0; i < 12; i++) {
        if (IntSe[i].se == 0) {
            IntSe[i].distance = distance;
            IntSe[i].se = se;
            IntSe[i].x = x;
            IntSe[i].z = z;
            IntSe[i].timer = 15;
            return IntSe[i].handle = TEA_SeOn(se, x, z);
        }
    }
    return 0;
}
}
