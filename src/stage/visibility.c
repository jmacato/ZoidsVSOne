#include "game_camera.h"
#include "joint.h"
#include "zoid.h"

extern CameraState *camTmp;
extern s32 ctrlZoid;
extern f32 sPassage(Vec3 *, Vec3 *, Vec3 *);

extern s32 sDispClipOnOff;

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

s32 grdCamChkObjR(HSD_JObj *joint)
{
    f32 dx;
    f32 dz;
    f32 forward;
    f32 side;

    if (joint == 0)
        return 0;
    dx = joint->matrix[0][3] - camTmp->relative_origin.x;
    dz = joint->matrix[2][3] - camTmp->relative_origin.z;
    if (sDispClipOnOff == 2) {
        if (absf(dx) > 600.0f)
            return 0;
        if (absf(dz) > 600.0f)
            return 0;
    }
    if (dx * dx + dz * dz > 360000.0f)
        return 0;
    side = dx * camTmp->planar[0] - dz * camTmp->planar[1];
    forward = dx * camTmp->planar[1] + dz * camTmp->planar[0];
    if (forward < -600.0f)
        return 0;
    if (forward > 1100.0f)
        return 0;
    if (side > 1000.0f)
        return 0;
    if (side < -1000.0f)
        return 0;
    if (side - forward > 600.0f)
        return 0;
    if (side + forward < -600.0f)
        return 0;
    return 1;
}

s32 grdCamChkR(HSD_JObj *joint)
{
    f32 dx;
    f32 dz;
    f32 forward;
    f32 side;

    dx = joint->matrix[0][3] - camTmp->relative_origin.x;
    dz = joint->matrix[2][3] - camTmp->relative_origin.z;
    if (sDispClipOnOff == 2) {
        if (absf(dx) > 250.0f)
            return 0;
        if (absf(dz) > 250.0f)
            return 0;
    }
    if (dx * dx + dz * dz > 1210000.0f)
        return 0;
    side = dx * camTmp->planar[0] - dz * camTmp->planar[1];
    forward = dx * camTmp->planar[1] + dz * camTmp->planar[0];
    if (forward < -390.0f)
        return 0;
    if (forward > 1100.0f)
        return 0;
    if (side > 1000.0f)
        return 0;
    if (side < -1000.0f)
        return 0;
    if (side - forward > 600.0f)
        return 0;
    if (side + forward < -600.0f)
        return 0;
    return 1;
}

f32 grdCamChkS(HSD_JObj *joint)
{
    Vec3 point;
    point.x = joint->matrix[0][3];
    point.y = joint->matrix[1][3];
    point.z = joint->matrix[2][3];
    return sPassage(&camTmp->relative_origin, (Vec3 *)Zoid[ctrlZoid].position, &point);
}
