#include "zoid.h"
#include "game_camera.h"
#include "game_pad.h"
#include "math_support.h"
#include "angle.h"

extern void camDispZoid(CameraState *camera, ZoidState *zoid, ZoidControlData *control);
extern void zdWeaponChg(ZoidState *zoid);
extern void zdWeaponFireON(ZoidState *zoid);
extern void zdWeaponFireOFF(ZoidState *zoid);
extern void zdAtack1(ZoidState *zoid);
extern void ZoidSearchNextTarget(ZoidState *zoid);
extern void zdStep0f(ZoidState *zoid, f32 angle);
extern void TEA_VoiceOn(u8 character, s32 voice);
extern void PartnerFace(s32 face, s32 frames);
extern void angLimit(f32 *angle);
extern f32 atan2f(f32 y, f32 x);
extern s32 sCamMuteki;
extern s32 gameTime;
extern s32 padBy;
extern s32 rumble;
extern s32 dspPartnerMsgTm;

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void sCameraCtrl(CameraState *camera)
{
    PadState *pad;
    ZoidState *zoid;
    ZoidControlData *control;
    ZoidAIState *ai;
    ZoidState *partner;
    s32 saved;
    s32 mode;
    s32 i;
    s32 old;
    s32 fire;
    s8 started;
    s8 was_held;
    s8 held;
    f32 x;
    f32 y;
    f32 magnitude;
    f32 sx;
    f32 sy;
    f32 length;
    f32 angle;
    s32 frame_padding[3];
    f32 previous;
    f32 delta;
    f32 tilt;
    s32 unused2[1];
    f32 scale;

    if (camera != 0 && camera->cobj != 0 && (pad = camera->pad) != 0) {
        control = 0;
        if ((zoid = camera->zoid, camera->zoid != 0)) {
            control = zoid->control;
        }
        if (sCamMuteki != 0) {
            zoid->health = zoid->max_health;
            gameTime = -1;
        }
        if (sCamMuteki == 2) {
            for (i = 0; i < 16; i++) {
                if (Zoid[i].joint != 0) {
                    Zoid[i].health = Zoid[i].max_health;
                }
            }
        }
        scale = (f32)padBy / 100.0;
        if (zoid->booster_on != 0) {
            scale = 4.0 * ((f32)padBy / 100.0);
        }
        saved = camera->field_164;
        sCameraTargetZoid(camera, &Zoid[camera->target_index]);
        if (zoid != 0) {
            pad->rumble = zoid->rumble_timer != 0;
        } else {
            pad->rumble = 0;
        }
        if (rumble == 0) {
            pad->rumble = 0;
        }
        camDispZoid(camera, zoid, control);
        camera->field_164 = saved;
        fire = 0;
        if (pad->a != 0 && pad->x != 0) {
            fire = 1;
        }
        zoid->super_attack_input = fire;
        if ((s8)zoid->option_use_state != 0) {
            zoid->super_attack_input = 0;
        }
        if (zoid->death_started != 0) {
            zoid->super_attack_input = 0;
        }
        if (pad->pressed_b != 0) {
            camera->zoid->requested_action = ZOID_ACTION_JUMP_2;
        }
        if (pad->pressed_y != 0) {
            zdWeaponChg(zoid);
        }
        if (zoid->super_attack_input == 0) {
            if (pad->a != 0) {
                zdWeaponFireON(zoid);
            } else {
                zdWeaponFireOFF(zoid);
            }
            if (pad->pressed_x != 0) {
                zdAtack1(zoid);
            }
        }
        if (pad->pressed_r != 0) {
            ZoidSearchNextTarget(camera->zoid);
        }
        if (pad->pressed_l != 0 && camera->zoid != 0) {
            camera->zoid->target_pending = 0;
        }
        zoid->option_use_state = pad->z;
        if (zoid->death_started != 0) {
            zoid->option_use_state = 0;
        }
        sx = pad->substick_x;
        sy = pad->substick_y;
        magnitude = sx * sx + sy * sy;
        was_held = camera->substick_held;
        held = was_held;
        if (magnitude < 0.1) {
            held = 0;
        }
        if (magnitude > 0.3) {
            held = 1;
        }
        started = held != 0 && was_held == 0;
        camera->substick_held = held;
        if (started != 0) {
            angle = atan2f(-sx, sy);
            zdStep0f(zoid, angle + camera->yaw - zoid->heading);
        }
        if (zoid != 0 && zoid->index == 0 && Zoid[2].joint != 0 && zoid->slot == Zoid[2].slot) {
            partner = &Zoid[2];
            ai = partner->ai;
            if (partner->death_started != 0) {
                ai = 0;
            }
            if (ai != 0) {
                old = ai->partner_command;
                if (dspPartnerMsgTm == 0) {
                if (pad->pressed_dpad_left != 0) {
                    ai->partner_command = AI_PARTNER_KEEP_DISTANCE;
                }
                if (pad->pressed_dpad_right != 0) {
                    ai->partner_command = AI_PARTNER_CLOSE_COMBAT;
                }
                if (pad->pressed_dpad_up != 0 && zoid->target_pending != 0) {
                    ai->partner_command = AI_PARTNER_ATTACK_LOCKED;
                }
                if (ai->partner_command == AI_PARTNER_ATTACK_LOCKED && zoid->target_pending == 0) {
                    ai->partner_command = AI_PARTNER_NONE;
                }
                if (pad->pressed_dpad_down != 0) {
                    ai->partner_command = AI_PARTNER_COME_NEAR;
                }
                if (zoid->death_started != 0) {
                    ai->partner_command = old;
                }
                if (old != ai->partner_command && ai->partner_command != AI_PARTNER_NONE) {
                    TEA_VoiceOn(partner->person, 11);
                    PartnerFace(5, 60);
                }
            }
            }
        }
        y = pad->stick_y * scale;
        x = pad->stick_x * scale;
        length = square_root(x * x + y * y);
        if (length < 0.05) {
            zoid->stick_length = 0.0f;
            zoid->stick_length = 0.0f;
            return;
        }
        zoid->stick_length = length;
        angle = atan2f(-x, y);
        previous = zoid->stick_angle;
        angLimit(&angle);
        zoid->step_heading = angle + camera->yaw;
        zoid->stick_angle = angle;
        zoid->stick_x = x;
        zoid->stick_y = y;
        angLimit(&zoid->step_heading);
        delta = angle - previous;
        angLimit(&delta);
        if (0.0f == length) {
            zoid->stick_frames = 0.0f;
        } else {
            zoid->stick_frames += 1.0f;
        }
        if (0.0f == length) {
            zoid->stick_steady_frames = 0.0f;
        } else if (absf(delta) > DEG2RAD_D(10.0)) {
            zoid->stick_steady_frames = 0.0f;
        } else {
            zoid->stick_steady_frames += 1.0f;
        }
        if (control != 0) {
            mode = control->field_0140[zoid->weapon_mount];
            if (mode == 2) {
                tilt = -zoid->stick_x * (2.0 * (3.1415926 * (f32)(control->stick_turn_rate / 1000.0)) / 360.0);
                tilt += zoid->heading;
                angLimit(&tilt);
                zoid->heading = tilt;
            }
            if (mode == 2) {
                tilt = -zoid->stick_y * (2.0 * (3.1415926 * (f32)(control->stick_turn_rate / 1000.0)) / 360.0);
                tilt += zoid->pitch;
                angLimit(&tilt);
            } else {
                tilt = zoid->pitch;
                if (tilt < 0.0f) {
                    tilt += DEG2RAD_D(0.3f);
                    if (tilt > 0.0f) {
                        tilt = 0.0f;
                    }
                }
                if (tilt > 0.0f) {
                    tilt -= DEG2RAD_D(0.3f);
                    if (tilt < 0.0f) {
                        tilt = 0.0f;
                    }
                }
            }
            angLimit(&tilt);
            if (tilt > DEG2RAD_D(15.0)) {
                tilt = (f32)DEG2RAD_D(15.0);
            }
            if (tilt < -DEG2RAD_D(15.0)) {
                tilt = (f32)-DEG2RAD_D(15.0);
            }
            zoid->pitch = tilt;
        }
    }
}
