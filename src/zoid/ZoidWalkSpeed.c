#include "zoid.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern u32 vsyncN;
extern f64 sin(f64 x);
extern void angLimit(f32 *angle);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void setAnimRateXor(HSD_JObj *joint, f32 rate, HSD_JObj *exclude);

static inline f32 fabsf(f32 *v)
{
    return (*(u32 *)v &= 0x7FFFFFFF, *v);
}

void ZoidWalkSpeed(ZoidState *zoid)
{
    s32 anim;
    s32 cur;
    s32 mode;
    s32 half;
    s32 broken;
    s32 sub;
    f32 max;
    ZoidControlData *control;
    s32 slow;
    f32 speed;
    f32 steer;
    f32 diff;

    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    control = zoid->control;
    half = 0;
    zoid->max_speed = control->base_max_speed + zoid->speed_bonus;
    cur = mode = zoid->current_animation;
    anim = mode;
    speed = zoid->field_1A74;
    steer = zoid->steer;
    if ((mode == 2 || mode == 3 || mode == 4) && control->field_00F8 == 0)
        half = 1;
    if (control->field_00F4 == 0)
        half = 0;
    if (zoid->feet[2].joint == 0 && zoid->feet[3].joint == 0)
        half = 0;
    if (half != 0 && zoid->feet[2].joint != 0 && zoid->feet[2].no_contact_frames < 90)
        half = 0;
    if (half != 0 && zoid->feet[3].joint != 0 && zoid->feet[3].no_contact_frames < 90)
        half = 0;
    if (half != 0 && zoid->feet[0].joint != 0 && zoid->feet[0].no_contact_frames < 90)
        half = 0;
    if (half != 0) {
        zoid->ramped_speed *= 0.5f;
        zoid->field_1A74 *= 0.5f;
        zoid->forward_speed *= 0.5f;
    }
    broken = 0;
    if (zoid->damages[4].maximum_health != 0 && zoid->damages[4].health == 0)
        broken |= 1;
    if (zoid->damages[5].maximum_health != 0 && zoid->damages[5].health == 0)
        broken |= 2;
    if (zoid->damages[2].maximum_health != 0 && zoid->damages[2].health == 0)
        broken |= 4;
    if (zoid->damages[3].maximum_health != 0 && zoid->damages[3].health == 0)
        broken |= 8;
    if (zoid->damages[0].maximum_health != 0 && zoid->damages[0].health == 0)
        broken |= 16;
    if ((broken & 3) && (mode == 3 || mode == 4) && mode != 3) {
        slow = 0;
        if (broken & 1)
            slow = 5;
        if (broken & 2)
            slow += 5;
    }
    if ((broken & 0x10) && (mode == 3 || mode == 4)) {
        angLimit(&steer);
        if (speed >= 0.5) {
            steer = steer / 2.0;
            steer = DEG(10) * ((1.0 + sin(3.141592 * (vsyncN * 2) / 120.0)) / 2.0) + steer;
            if (steer > DEG(175))
                steer = DEG(175);
            if (steer < -DEG(175))
                steer = -DEG(175);
        }
    }
    if (0.0f < speed && speed < 0.1)
        speed = 0.0f;
    if (speed < -0.3)
        speed = -0.3f;
    if (-0.05 < speed && speed < 0.0f)
        speed = 0.0f;
    if (speed < 0.5) {
        diff = steer;
        if (fabsf(&diff) < 0.02)
            steer = 0.0f;
    }
    sub = 0;
    if (broken & 0xC)
        sub = 10;
    max = DEG((f32)(control->max_steer + zoid->turn_bonus - sub));
    if (max < 0.0f)
        max = 0.0f;
    if (steer > max)
        steer = max;
    if (steer < -max)
        steer = -max;
    if (0.0f == speed)
        steer = 0.0f;
    if (0.0f != steer && 0.0f == speed) {
        speed = 0.1f;
        if (zoid->ramped_speed < 0.1)
            zoid->ramped_speed = speed;
    }
    zoid->field_1A74 = speed;
    speed = zoid->ramped_speed;
    if (0.0f < speed && speed < 0.1)
        speed = 0.0f;
    if (-0.05 < speed && speed < 0.0f)
        speed = 0.0f;
    max = (zoid->max_speed - slow) / 100.0;
    if (speed > max && zoid->booster_on == 0)
        speed = max;
    if (speed > zoid->max_speed / 100.0)
        anim = 5;
    else if (speed > control->anim4_min_speed / 100.0)
        anim = 4;
    else if (speed >= 0.1)
        anim = 3;
    else if (0.0f == speed)
        anim = 1;
    else if (speed < 0.0f)
        anim = 6;
    if (zoid->booster_on == 0 && anim == 5)
        anim = 4;
    if (anim == 3 || anim == 4 || anim == 5) {
        if (anim != cur) {
            if (cur == 3 || cur == 4 || cur == 5) {
                if (zoid->field_1B30 < 15) {
                    zoid->field_1B30++;
                    anim = cur;
                } else {
                    zoid->field_1B30 = 0;
                }
            } else {
                zoid->field_1B30 = 120;
            }
        } else {
            zoid->field_1B30++;
        }
    } else {
        zoid->field_1B30++;
    }
    if (anim != 1)
        zoid->anim1_frames = 0;
    if (anim == 1 && zoid->anim1_frames > 600) {
        zoid->anim1_frames = 0;
        anim = 2;
    }
    if (zoid->current_animation == 2 && anim == 1)
        anim = 2;
    zoid->anim1_frames++;
    if (zoid->current_animation == 2 && zoid->animation_stopped != 0)
        anim = 1;
    if (anim != zoid->current_animation)
        ZoidSetAnim(zoid, anim);
    if (anim == 6)
        setAnimRateXor(zoid->joint, (f32)-control->anim6_rate * speed, zoid->animation_exclusion);
    if (anim == 3)
        setAnimRateXor(zoid->joint, (f32)control->anim3_rate * speed, zoid->animation_exclusion);
    if (anim == 4)
        setAnimRateXor(zoid->joint, 0.1 * control->anim4_rate * speed, zoid->animation_exclusion);
    if (anim == 5)
        setAnimRateXor(zoid->joint, 0.1 * control->anim5_rate * speed, zoid->animation_exclusion);
    zoid->steer = steer;
    if (zoid->forward_speed > 0.0f)
        zoid->heading += 0.1 * zoid->steer;
    if (zoid->forward_speed < 0.0f)
        zoid->heading -= 0.1 * zoid->steer;
}
