#include "zoid.h"
#include "game_camera.h"
#include "game_mode.h"
#include "ground_collision.h"

#pragma auto_inline off
extern void camR_jobj(CameraRange *range, HSD_JObj *joint);
extern void camR_thj(CameraRange *range, HSD_JObj *joint, u32 *flags, u32 mask);

extern s32 SE_TableList[];
extern s32 IntSeSet(s16 se, f32 distance, f32 x, f32 z);
extern f32 cosf(f32);
extern f32 sinf(f32);

static inline void PAD_STACK(void)
{
    s32 frame_padding[1];
    frame_padding[0] = 0;
}

s32 camSe(CameraState *camera, s16 sound, Vec3 *point)
{
    Vec3 relative;
    f32 distance;
    s16 se;

    if (sound < 0)
        return 0;
    if (GameMode.game_type != GAME_TYPE_VS) {
        sCameraRela(camera, point, &relative);
        distance = relative.x * relative.x + relative.z * relative.z;
        if (distance > 90000.0f)
            return 0;
    } else {
        relative.x = 0.0f;
        relative.z = 100.0f;
        distance = 100.0f;
    }
    se = SE_TableList[sound];
    if (se < 0)
        return 0;
    return IntSeSet(se, distance, relative.x, -relative.z);
}


void camR_len(CameraRange *range, ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        camR_jobj(range, zoid->camera_joint);
        camR_jobj(range, zoid->head_coobj.joint);
        camR_jobj(range, zoid->feet[1].joint);
        camR_jobj(range, zoid->feet[2].joint);
        camR_jobj(range, zoid->tail_coobjs[0].joint);
    }
}


void camR_thj(CameraRange *range, HSD_JObj *joint, u32 *flags, u32 mask)
{
    Vec3 position;
    s32 unused[1];

    if (joint == 0)
        return;
    position.x = joint->matrix[0][3];
    position.y = joint->matrix[1][3];
    position.z = joint->matrix[2][3];
    if (sColPt(&range->origin, &position, (GroundMask){{0, 255, 0, 0}}) == GROUND_NO_HIT)
        *flags |= mask;
    PAD_STACK();
}

void camR_th(CameraRange *range, ZoidState *zoid, u32 *flags)
{
    if (flags == 0)
        return;
    if (zoid == 0) {
        *flags = 0xffffffff;
        return;
    }
    if (zoid->joint != 0) {
        camR_thj(range, zoid->camera_joint, flags, 1);
        camR_thj(range, zoid->head_coobj.joint, flags, 2);
    }
}
