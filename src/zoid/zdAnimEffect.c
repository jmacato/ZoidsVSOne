#include "zoid.h"
#include "game_camera.h"
#include "game_zoid_data.h"

extern s32 gameEndF;
extern CameraState *camTmp;
extern s32 camSe(CameraState *camera, s16 sound, Vec3 *point);
extern void zdEffectMount(ZoidState *zoid, s32 mount, s32 effect);

void zdAnimEffect(ZoidState *zoid, s32 animation)
{
    s32 sound = Tea_zoiddat[zoid->type].animation_sounds[animation];
    s32 effect = Tea_zoiddat[zoid->type].animation_effects[animation];
    s32 mount = Tea_zoiddat[zoid->type].animation_effect_mounts[animation];

    if (sound > 0 && gameEndF <= 2)
        camSe(camTmp, sound, (Vec3 *)zoid->position);
    if (effect < 110 && effect > 0 && mount < 27 && mount >= 0)
        zdEffectMount(zoid, mount, effect);
}
