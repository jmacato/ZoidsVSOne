#pragma readonly_strings on
#include "zoid.h"
#include "game_camera.h"
typedef struct GroundMask {
    u8 bits[4];
} GroundMask;

#define NULL 0

extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern f32 sColPosAndY(Vec3 *point, u16 *selector, GroundMask mask);
extern f32 calcAng(Vec3 *from, Vec3 *to);
extern void camR_len(CameraRange *range, ZoidState *zoid);
extern void camR_th(CameraRange *range, ZoidState *zoid, s32 *flags);
extern s32 bitN(u32 bits);
extern void putErr(char *message);
extern void HSD_CObjSetInterest(struct HSD_CObj *cobj, Vec3 *interest);
extern void HSD_CObjSetEyePosition(struct HSD_CObj *cobj, Vec3 *position);
extern void sCameraCalc(CameraState *camera);


static inline GroundMask camMaskB(void)
{
    GroundMask mask;

    mask = (GroundMask){{0, 255, 0, 0}};
    return mask;
}

static inline GroundMask litMask(void)
{
    return (GroundMask){{0, 255, 0, 0}};
}

static inline GroundMask camMask(void)
{
    return camMaskB();
}


void camOn(CameraState *camera)
{
    Vec3 mine;
    Vec3 other;
    Vec3 interest;
    f32 angle;
    f32 yaw;
    s32 t;
    s32 order[16];
    s32 j;
    s32 i;
    s32 n;
    f32 *p;
    CameraRange *b;
    ZoidState *zoid;
    ZoidState *look;
    ZoidState *target;
    CameraRange *range;
    CameraRange *a;

    zoid = camera->zoid;
    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    target = NULL;
    /* unused mask temporaries keep the original stack frame size */
    camMaskB();
    camMaskB();
    camMaskB();
    camMaskB();
    camMaskB();
    look = NULL;
    mine.x = zoid->camera_joint->matrix[0][3];
    mine.y = zoid->camera_joint->matrix[1][3];
    mine.z = zoid->camera_joint->matrix[2][3];
    if (zoid->target_pending != 0) {
        target = &Zoid[zoid->target_slot];
        if (target->joint == NULL)
            target = NULL;
    }
    if (target == NULL)
        zoid->target_pending = 0;
    if (target != NULL) {
        look = target;
        other.x = target->camera_joint->matrix[0][3];
        other.y = target->camera_joint->matrix[1][3];
        other.z = target->camera_joint->matrix[2][3];
        if (other.x == mine.x && other.z == mine.z)
            look = NULL;
    }
    if (look == NULL) {
        angle = zoid->steer / 2.0f + zoid->heading;
        angLimit(&angle);
        other.x = mine.x;
        other.y = mine.y;
        other.z = mine.z;
        other.x = 100.0f * sinf(angle) + other.x;
        yaw = angle;
        other.z = 100.0f * cosf(yaw) + other.z;
    }
    p = &interest.x;
    for (i = 0; i < 3; i++, p++)
        *p = sLiner((&other.x)[i], (&mine.x)[i], 0.5f);
    yaw = calcAng(&other, &mine);
    if (100.0f == yaw)
        yaw = zoid->heading;
    for (i = 0; i < 16; i++) {
        range = &camera->range[i];
        camera->range[i].heading = 6.2831852 * (f32)i / 16.0 + yaw;
        /* no-op compare, needed for the original register allocation */
        (void) (0.0f == interest.x);
        camera->range[i].radius = 0.0f;
        camera->range[i].height = 0.0f;
        camera->range[i].score = 0;
        camera->range[i].origin.x = interest.x;
        camera->range[i].origin.y = interest.y;
        camera->range[i].origin.z = interest.z;
        camR_len(range, zoid);
        camR_len(range, target);
        range->origin.x += range->radius * sinf(range->heading);
        range->origin.z += range->radius * cosf(range->heading);
        range->height = range->origin.y = 3.0f + sColPosAndY(&range->origin, 0, (GroundMask){{0, 255, 0, 0}});
        range->visible = 0;
        range->target_visible = 0;
        camR_th(range, zoid, &range->visible);
        range->score = bitN(range->visible) << 20;
        camR_th(range, target, &range->target_visible);
        range->score += bitN(range->target_visible) << 12;
        if (range->radius < 200.0f)
            range->score |= 0x2710000;
    }
    for (i = 0; i < 16; i++)
        order[i] = i;
    order[0] = 2;
    order[8] = 10;
    for (i = 0; i < 15; i++) {
        for (j = i + 1; j < 16; j++) {
            a = &camera->range[order[i]];
            b = &camera->range[order[j]];
            if (a->score > b->score)
                continue;
            if (a->score == b->score && a->radius <= b->radius)
                continue;
            t = order[i];
            order[i] = order[j];
            order[j] = t;
        }
    }
    if (order[0] < 0 || order[0] >= 16)
        putErr("\x83J\x83\x81\x83\x89\x81H"); /* Shift-JIS "kamera?" */
    camera->range_timer++;
    range = &camera->range[camera->range_index];
    if ((range->visible & 3) != 3 && (range->target_visible & 3) != 3 && camera->range_timer > 180) {
        for (i = camera->range_index, n = 0; n < 16; n++, i++) {
            if (i >= 16)
                i = 0;
            range = &camera->range[i];
            if ((range->visible & 3) == 3 && (range->target_visible & 3) == 3 && !(range->radius > 150.0f))
                break;
        }
        if (n == 16)
            i = order[0];
        if (i != camera->range_index)
            camera->range_timer = 0;
        camera->range_index = i;
    }
    /* [3] is range[].visible; the member form does not match */
    if ((((s32 *)&camera->range[camera->range_index])[3] & 3) != 3 && camera->range_timer > 60) {
        for (i = camera->range_index, n = 0; n < 16; n++, i++) {
            if (i >= 16)
                i = 0;
            range = &camera->range[i];
            if ((range->visible & 3) == 3 && range->target_visible != 0 && !(range->radius > 100.0f))
                break;
        }
        if (n == 16)
            i = order[0];
        if (i != camera->range_index)
            camera->range_timer = 0;
        camera->range_index = i;
    }
    if (((s32 *)&camera->range[camera->range_index])[3] == 0) {
        for (i = camera->range_index, n = 0; n < 16; n++, i++) {
            if (i >= 16)
                i = 0;
            range = &camera->range[i];
            if (range->visible != 0 && !(range->radius > 80.0f))
                break;
        }
        if (n == 16)
            i = order[0];
        if (i != camera->range_index)
            camera->range_timer = 0;
        camera->range_index = i;
    }
    if (((s32 *)&camera->range[camera->range_index])[3] == 0) {
        for (i = camera->range_index, n = 0; n < 16; n++, i++) {
            if (i >= 16)
                i = 0;
            if (camera->range[i].visible != 0)
                break;
        }
        if (n == 16)
            i = order[0];
        if (i != camera->range_index)
            camera->range_timer = 0;
        camera->range_index = i;
    }
    i = camera->range_index;
    if (i < 0 || i >= 16)
        i = 0;
    camera->range_index = i;
    range = &camera->range[i];
    camera->interest.x = interest.x;
    camera->eye.x = range->origin.x;
    camera->relative_origin.x = range->origin.x;
    camera->interest.y = interest.y;
    camera->eye.y = range->origin.y;
    camera->relative_origin.y = range->origin.y;
    camera->interest.z = interest.z;
    camera->eye.z = range->origin.z;
    camera->relative_origin.z = range->origin.z;
    HSD_CObjSetInterest(camera->cobj, &camera->interest);
    HSD_CObjSetEyePosition(camera->cobj, &camera->eye);
    sCameraCalc(camera);
    camera->saved_eye.x = camera->eye.x;
    camera->saved_interest.x = camera->interest.x;
    camera->saved_eye.y = camera->eye.y;
    camera->saved_interest.y = camera->interest.y;
    camera->saved_eye.z = camera->eye.z;
    camera->saved_interest.z = camera->interest.z;
}
