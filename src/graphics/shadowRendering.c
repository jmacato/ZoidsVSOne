#pragma readonly_strings on
#include "shadow.h"
#include "game_camera.h"
#include "video.h"
#include "lobj.h"
#include "angle.h"

extern CameraState *camTmp;
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern void shadowSetZoid(HSD_Shadow *shadow, s32 index);

static inline void *HSD_ShadowGetUserData(HSD_Shadow *shadow)
{
    if (shadow == 0)
        __assert("shadow.h", 128, "shadow");
    return shadow->user_data;
}

static inline void HSD_ShadowSetIntensity(HSD_Shadow *shadow, u8 intensity)
{
    if (shadow == 0)
        __assert("shadow.h", 102, "shadow");
    shadow->intensity = intensity;
}

void shadowRendering(HSD_Shadow *shadow, s32 index)
{
    HSD_LObj *light;
    Vec3 interest;
    HSD_ViewingRect rect;
    Vec3 eye;
    Vec3 up;
    Vec3 position;
    u8 frame_padding[0x30];
    f32 size = 10.0f;
    f32 angle;

    light = HSD_ShadowGetUserData(shadow);
    if (light->flags & LOBJ_HIDDEN) {
        return;
    }
    shadowSetZoid(shadow, index);
    interest.x = camTmp->relative_origin.x;
    interest.y = camTmp->relative_origin.y;
    interest.z = camTmp->relative_origin.z;
    position.x = camTmp->relative_origin.x;
    position.y = 800.0f + camTmp->relative_origin.y;
    position.z = camTmp->relative_origin.z;
    HSD_CObjSetInterest(shadow->camera, &interest);
    HSD_CObjSetEyePosition(shadow->camera, &position);
    HSD_CObjGetEyePosition(shadow->camera, &eye);
    HSD_CObjGetUpVector(shadow->camera, &up);
    HSD_ViewingRectInit(&rect, &eye, &interest, &up, (light->flags & (u32)LOBJ_TYPE_MASK) == (u32)LOBJ_INFINITE ? 0 : 1);
    HSD_ViewingRectAddRect(&rect, &interest, size, -size, -size, size);
    eye.x = interest.x + 80.0f * sinf(camTmp->yaw);
    eye.y = interest.y;
    eye.z = interest.z + 80.0f * cosf(camTmp->yaw);
    HSD_ViewingRectAddRect(&rect, &eye, size, -size, -size, size);
    angle = camTmp->yaw;
    angle += (f32)DEG2RAD_D(45.0);
    eye.x = interest.x + 80.0f * sinf(angle);
    eye.y = interest.y;
    angle = camTmp->yaw;
    angle += (f32)DEG2RAD_D(45.0);
    eye.z = interest.z + 80.0f * cosf(angle);
    HSD_ViewingRectAddRect(&rect, &eye, size, -size, -size, size);
    eye.x = interest.x + 80.0f * sinf(camTmp->yaw - (f32)DEG2RAD_D(45.0));
    eye.y = interest.y;
    eye.z = interest.z + 80.0f * cosf(camTmp->yaw - (f32)DEG2RAD_D(45.0));
    HSD_ViewingRectAddRect(&rect, &eye, size, -size, -size, size);
    if (HSD_ViewingRectCheck(&rect) != 0) {
        HSD_ShadowSetViewingRect(shadow, rect.top, rect.bottom, rect.left, rect.right);
    } else {
        HSD_ShadowSetViewingRect(shadow, size, -size, -size, size);
    }
    HSD_ShadowSetIntensity(shadow, 128);
    HSD_StartRender(HSD_RP_OFFSCREEN);
    HSD_ShadowInit(shadow);
    HSD_ShadowStartRender(shadow);
    HSD_ShadowEndRender(shadow);
    HSD_EndRender();
}
