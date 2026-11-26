#include "zoid_ai.h"

extern f64 __frsqrte(f64);
extern f32 atan2f(f32 y, f32 x);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern void angLimit(f32 *angle);
extern f32 sLenPoint3dR(Vec3 *point);

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

static inline f32 absf(f32 *value)
{
    *(u32 *)value &= 0x7FFFFFFF;
    return *value;
}

static inline f32 angleY(f32 x, f32 z)
{
    return atan2f(x, z);
}

void zdExecAI(ZoidState *zoid)
{
    f32 base;
    f32 pad0;
    Vec3 d;
    f32 angle;
    f32 turn;
    f32 pad1;
    volatile f32 root;
    f32 abs1;
    f32 abs2;
    ZoidAIState *ai;
    ZoidState *target;
    Vec3 *dest;
    f32 dist;
    f32 len;
    f32 sum;
    f32 t;
    s32 index;
    u32 flags;
    f32 unused[11];

    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    ai = zoid->ai;
    if (ai == 0)
        return;
    index = ai->target_index;
    if (index != -1 && zoid->target_visibility[index] == 0)
        index = -1;
    if (index == -1)
        target = 0;
    else
        target = &Zoid[index];
    if (target != 0 && target->joint == 0)
        target = 0;
    dist = ai->target_distance;
    switch (ai->mode) {
    case AI_MODE_NONE:
        return;
    case AI_MODE_POINT:
        dest = &ai->destination;
        base = 0.0f;
        break;
    case AI_MODE_TARGET:
        if (target == 0)
            return;
        dest = (Vec3 *)target->position;
        base = target->heading;
        break;
    case AI_MODE_RUN:
        zoid->step_heading = zoid->heading + (f32)ai->turn_speed;
        zoid->stick_length = 1.0f;
        angLimit(&zoid->step_heading);
        return;
    default:
        return;
    }
    if (ai->flags & 0x100) {
        if (dist < 1.0f)
            dist = 1.0f;
        sum = 0.0f;
        t = dest->x - ai->field_58.x;
        d.x = t;
        sum += t * t;
        t = dest->y - ai->field_58.y;
        d.y = t;
        sum += t * t;
        t = dest->z - ai->field_58.z;
        d.z = t;
        sum += t * t;
        len = sqrtf(sum, &root);
        if (0.0f == len) {
            ai->goal.x = ai->field_58.x;
            ai->goal.y = ai->field_58.y;
            ai->goal.z = ai->field_58.z;
        } else {
            ai->goal.x = ai->field_58.x - dist * d.x / len;
            ai->goal.y = ai->field_58.y - dist * d.y / len;
            ai->goal.z = ai->field_58.z - dist * d.z / len;
        }
    } else {
        d.x = zoid->position[0] - dest->x;
        d.y = zoid->position[1] - dest->y;
        d.z = zoid->position[2] - dest->z;
        turn = angle = angleY(d.x, d.z);
        len = sLenPoint3dR(&d);
        flags = ai->flags;
        switch (flags & AI_RADIUS_MASK) {
        case AI_RADIUS_EXACT:
            len = dist;
            break;
        case AI_RADIUS_IN:
            if (len >= dist)
                len = dist - 0.2;
            break;
        case AI_RADIUS_OUT:
            if (len <= dist)
                len = 0.2 + dist;
            break;
        }
        switch (flags & AI_ANGLE_MASK) {
        case AI_ANGLE_KEEP << AI_ANGLE_SHIFT:
            turn = base + ai->target_angle - angle;
            angLimit(&turn);
            if (turn > 2.0 * (3.1415926 * 30) / 360.0)
                turn = 2.0 * (3.1415926 * 30) / 360.0;
            if (turn < -(2.0 * (3.1415926 * 30) / 360.0))
                turn = -(2.0 * (3.1415926 * 30) / 360.0);
            angle = turn + angle;
            break;
        case AI_ANGLE_CIRCLE << AI_ANGLE_SHIFT:
            angle += 2.0 * (3.1415926 * (f32)ai->turn_speed) / 360.0;
            break;
        }
        angLimit(&angle);
        if (len < 0.0f)
            len = 0.0f;
        ai->goal.x = len * sinf(angle) + dest->x;
        ai->goal.z = len * cosf(angle) + dest->z;
        ai->goal.y = dest->y;
    }
    d.x = ai->goal.x - zoid->position[0];
    d.y = ai->goal.y - zoid->position[1];
    d.z = ai->goal.z - zoid->position[2];
    len = sLenPoint3dR(&d);
    if (len <= 3.0f) {
        zoid->stick_length = 0.0f;
        return;
    }
    base = (angle = angleY(d.x, d.z)) - zoid->heading;
    angLimit(&base);
    abs1 = base;
    if (absf(&abs1) > 2.0 * (3.1415926 * 80) / 360.0) {
        if (zoid->field_1A74 <= 0.01) {
            if (zoid->action == ZOID_ACTION_WALK && zoid->requested_action == 0) {
                if (base > 0.0f)
                    zoid->requested_action = ZOID_ACTION_TURN_L0;
                else
                    zoid->requested_action = ZOID_ACTION_TURN_R0;
                zoid->stick_length = 1.0f;
            }
        } else if (zoid->action == ZOID_ACTION_TURN_L0 || zoid->action == ZOID_ACTION_TURN_R0) {
            zoid->stick_length = 1.0f;
        } else {
            zoid->stick_length = 0.0f;
        }
    } else {
        if ((zoid->action == ZOID_ACTION_TURN_L0 || zoid->action == ZOID_ACTION_TURN_R0) && (abs2 = base, absf(&abs2)) < 2.0 * (3.1415926 * 20) / 360.0) {
            zoid->stick_length = 0.0f;
            return;
        }
        zoid->step_heading = angle;
        zoid->stick_length = 0.3f;
        if (len > 3.0f)
            zoid->stick_length = 1.0f;
        if (len <= 0.1)
            zoid->stick_length = 0.0f;
    }
}
