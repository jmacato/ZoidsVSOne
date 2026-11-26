#include "zoid.h"

extern void __assert(const char *file, s32 line, const char *message);
extern f32 atan2f(f32 y, f32 x);

static inline f32 HSD_JObjGetTranslationX(HSD_JObj *joint)
{
    if (joint == 0) __assert("jobj.h", 1009, "jobj");
    return joint->translation.x;
}
static inline f32 HSD_JObjGetTranslationZ(HSD_JObj *joint)
{
    if (joint == 0) __assert("jobj.h", 1033, "jobj");
    return joint->translation.z;
}

void sSetRxRzF(ZoidState *zoid, FootJoint *front, FootJoint *back, f32 *rx, f32 *rz)
{
    f32 bz;
    f32 bx;
    f32 y;
    f32 dy;
    f32 angle;
    u8 frame_padding[0x38];

    if (front->joint == 0) {
        return;
    }
    if (back->joint == 0) {
        return;
    }
    y = (front->ground + back->ground) / 2.0f;
    HSD_JObjGetTranslationX(back->joint);
    HSD_JObjGetTranslationX(front->joint);
    bz = HSD_JObjGetTranslationZ(back->joint);
    angle = HSD_JObjGetTranslationZ(front->joint);
    bz = (angle + bz) / 2.0f;
    angle = atan2f(zoid->position[1] - y, bz);
    *rx = *rx + (angle - *rx) * 0.25;
    dy = front->ground - back->ground;
    bx = HSD_JObjGetTranslationX(back->joint);
    angle = atan2f(dy, HSD_JObjGetTranslationX(front->joint) - bx);
    *rz = *rz + (angle - *rz) * 0.25;
}
