#pragma readonly_strings on
#include "game_camera.h"
#include "zoid.h"
typedef struct GroundMask {
    u8 bits[4];
} GroundMask;

#define NULL 0

extern void GXProject(f32 x, f32 y, f32 z, f32 view[3][4], f32 *projection, f32 *viewport, f32 *sx, f32 *sy,
                      f32 *sz);

#pragma force_active on
/* unreferenced: four 320x240 screen quadrants as {xmin, xmax, ymin, ymax} */
static const s16 sQuadrantRectsA[16] = { 0, 320, 0, 240, 0, 320, 240, 480, 320, 640, 0, 240, 320, 640, 240, 480 };
static const s16 sQuadrantRectsB[16] = { 0, 320, 0, 240, 0, 320, 240, 480, 320, 640, 0, 240, 320, 640, 240, 480 };
#pragma force_active off

extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 sColPt(Vec3 *first, Vec3 *second, GroundMask mask);
extern f32 sColPosAndY(Vec3 *point, u16 *selector, GroundMask mask);

static inline GroundMask camMaskB(void)
{
    GroundMask mask;

    mask = (GroundMask){{0, 255, 0, 0}};
    return mask;
}

static inline GroundMask camMask(void)
{
    return camMaskB();
}

static inline GroundMask litMask(void)
{
    return (GroundMask){{0, 255, 0, 0}};
}

static inline GroundMask wallMaskB(void)
{
    GroundMask mask;

    mask = (GroundMask){{0, 255, 0, 0}};
    return mask;
}

static inline GroundMask wallMask(void)
{
    return wallMaskB();
}

void camInMine(CameraState *camera, ZoidState *zoid)
{
    static char *str00 = "01234567890123456789";
    ZoidControlData *control;
    CameraMountInfo *mount;
    HSD_JObj *joint;
    Vec3 mine;
    Vec3 pos;
    f32 angle;
    f32 y;
    f32 fraction;
    s32 i;
    f32 unused[2];

    if (zoid == 0)
        return;
    control = zoid->control;
    /* unused mask temporaries keep the original stack frame size */
    camMaskB();
    camMaskB();
    litMask();
    mine.x = zoid->camera_joint->matrix[0][3];
    mine.y = zoid->camera_joint->matrix[1][3];
    mine.z = zoid->camera_joint->matrix[2][3];
    for (i = 0; i < 20; i++) {
        mount = &control->camera_mounts[i];
        joint = zoid->weapon_slots[mount->joint_slot].joint;
        if (joint == 0) {
            camera->mount_hidden[i] = 1;
            continue;
        }
        angle = camera->focus_heading + (f32)mount->angle * 3.1415926 * 2.0 / 360.0;
        /* no-op compare, needed for the original register allocation */
        (void) (30.0 == mine.x);
        angLimit(&angle);
        camera->mount_positions[i].x = joint->matrix[0][3];
        camera->mount_positions[i].y = joint->matrix[1][3];
        camera->mount_positions[i].z = joint->matrix[2][3];
        camera->mount_positions[i].x += mount->distance * sinf(angle);
        camera->mount_positions[i].z += mount->distance * cosf(angle);
        camera->mount_positions[i].y += mount->height - 30.0;
        pos.x = camera->mount_positions[i].x;
        pos.y = camera->mount_positions[i].y;
        pos.z = camera->mount_positions[i].z;
        pos.y += 50.0f;
        y = sColPosAndY(&pos, 0, (GroundMask){{0, 255, 0, 0}}) + 5.0f;
        if (camera->mount_positions[i].y < y)
            camera->mount_positions[i].y = y;
        fraction = sColPt(&mine, &camera->mount_positions[i], (GroundMask){{0, 255, 0, 0}});
        camera->mount_hidden[i] = fraction != 10000.0f;
        if (fraction == 10000.0f)
            camera->mount_hidden[i] = 0;
        else
            camera->mount_hidden[i] = 1;
        str00[i] = camera->mount_hidden[i] ? 'x' : '0' + i % 10;
    }
}

typedef struct ScreenPoint {
    f32 x, y;
} ScreenPoint;

s32 sCameraIn(CameraState *camera, HSD_JObj *joint)
{
    f32 depth;
    ScreenPoint screen;
    f32 unused[2];
    s32 full[4] = { 10, 630, 10, 440 };
    s32 top[4] = { 10, 630, 10, 230 };
    s32 bottom[4] = { 10, 630, 250, 470 };
    s32 inner_full[4] = { 130, 400, 100, 360 };
    s32 inner_top[4] = { 130, 400, 60, 180 };
    s32 inner_bottom[4] = { 130, 400, 300, 420 };
    s32 x;
    s32 y;
    s32 *outer;
    s32 *inner;

    if (joint == NULL)
        return 1;
    GXProject(joint->matrix[0][3], joint->matrix[1][3], joint->matrix[2][3], camera->view, camera->projection,
              camera->viewport, &screen.x, &screen.y, &depth);
    x = screen.x;
    y = screen.y;
    if (depth >= 1.0)
        return 0;
    outer = full;
    inner = inner_full;
    if (sCamNN == 2) {
        if (camera->half == 0) {
            outer = top;
            inner = inner_top;
        } else {
            outer = bottom;
            inner = inner_bottom;
        }
    }
    if (x < outer[0])
        return 0;
    if (x > outer[1])
        return 0;
    if (y < outer[2])
        return 0;
    if (y > outer[3])
        return 0;
    if (x < inner[0])
        return 1;
    if (x > inner[1])
        return 1;
    if (y < inner[2])
        return 1;
    if (y > inner[3])
        return 1;
    return 2;
}
