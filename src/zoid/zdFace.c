#include "zoid.h"
#include "angle.h"

#define NULL 0

extern f64 __frsqrte(f64);
extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

static inline HSD_JObj *zdGetPos(ZoidState *z, Vec3 *v)
{
    f32 *dst;
    HSD_JObj *joint;

    joint = NULL;
    if (z->body_base_joint != NULL)
        joint = z->body_base_joint;
    dst = &v->x;
    if (joint != NULL) {
        *dst++ = joint->matrix[0][3];
        /* reads matrix[1][3] and matrix[2][3]; plain indexing changes the code */
        joint = (HSD_JObj *)((u8 *)joint + 16);
        *dst++ = joint->matrix[0][3];
        *dst++ = joint->matrix[1][3];
    } else {
        *dst++ = z->position[0];
        *dst++ = z->position[1];
        *dst++ = z->position[2];
    }
    return joint;
}

void zdFace(ZoidState *zoid)
{
    u8 pad0[4];
    f32 yaw;
    u8 pad1[4];
    f32 pitch;
    Vec3 pos;
    Vec3 tpos;
    f32 dist;
    f32 dy;
    f32 dz;
    ZoidState *target;
    f32 limit;
    f32 dx;
    u8 pad[16];
    volatile f32 root;

    if (zoid == NULL)
        return;
    if (zoid->joint == NULL)
        return;
    limit = 2.0 * (3.1415926 * (f32)zoid->control->max_face_yaw) / 360.0;
    if (zoid->face_lock != 0)
        limit = 0.0f;
    if (zoid->target_pending != 0) {
        target = &Zoid[zoid->target_slot];
        if (target->joint == NULL) {
            yaw = 0.0f;
            pitch = 0.0f;
        } else {
            zdGetPos(zoid, &pos);
            zdGetPos(target, &tpos);
            dz = tpos.z - pos.z;
            dx = tpos.x - pos.x;
            dy = tpos.y - pos.y;
            dist = sqrtf(dx * dx + dz * dz, &root);
            yaw = atan2f(dx, dz) - zoid->heading;
            angLimit(&yaw);
            pitch = atan2f(-dy, dist);
            angLimit(&pitch);
        }
    } else {
        yaw = 0.0f;
        pitch = 0.0f;
    }
    if (yaw < 0.0f && yaw < -limit)
        yaw = -limit;
    if (yaw > 0.0f && yaw > limit)
        yaw = limit;
    limit = DEG2RAD_F(60.0f);
    if (pitch < 0.0f && pitch < -limit)
        pitch = -limit;
    if (pitch > 0.0f && pitch > limit)
        pitch = limit;
    angLimit(&zoid->face_yaw);
    angLimit(&zoid->face_pitch);
    if (zoid->face_yaw > yaw) {
        zoid->face_yaw -= DEG2RAD_F(7.0f);
        if (zoid->face_yaw < yaw)
            zoid->face_yaw = yaw;
    }
    if (zoid->face_yaw < yaw) {
        zoid->face_yaw += DEG2RAD_F(7.0f);
        if (zoid->face_yaw > yaw)
            zoid->face_yaw = yaw;
    }
    if (zoid->face_pitch > pitch) {
        zoid->face_pitch -= DEG2RAD_F(0.2f);
        if (zoid->face_pitch < pitch)
            zoid->face_pitch = pitch;
    }
    if (zoid->face_pitch < pitch) {
        zoid->face_pitch += DEG2RAD_F(0.2f);
        if (zoid->face_pitch > pitch)
            zoid->face_pitch = pitch;
    }
}
