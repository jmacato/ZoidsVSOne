#include "game_pad.h"
#include "controller.h"

extern void HSD_PadRumbleOn(u8 port);
extern void HSD_PadRumbleOffN(u8 port);
extern void TEA_HotReset(u32 code);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

static inline void PAD_STACK(void)
{
    f32 frame_padding[10];
    frame_padding[0] = 0.0f;
}

void sPadGet1(s32 port)
{
    PadState *pad;
    HSD_PadStatus *copy;
    u32 trigger;
    u32 button;
    HSD_PadStatus *master;
    f32 x;
    f32 y;
    f32 ax;
    f32 ay;
    s32 flag;
    s32 reset;

    if (port < 0)
        return;
    if (port > 3)
        return;
    pad = &sPad[port];
    pad->previous_connected = pad->connected;
    copy = &HSD_PadCopyStatus[(u8)port];
    pad->connected = copy->err == 0;
    trigger = copy->trigger;
    pad->pressed_a = (trigger & 0x100) != 0;
    pad->pressed_b = (trigger & 0x200) != 0;
    pad->pressed_l = (trigger & 0x40) != 0;
    pad->pressed_r = (trigger & 0x20) != 0;
    pad->pressed_x = (trigger & 0x400) != 0;
    pad->pressed_y = (trigger & 0x800) != 0;
    pad->pressed_z = (trigger & 0x10) != 0;
    pad->pressed_start = (trigger & 0x1000) != 0;
    pad->pressed_dpad_left = (trigger & 0x1) != 0;
    pad->pressed_dpad_right = (trigger & 0x2) != 0;
    pad->pressed_dpad_up = (trigger & 0x8) != 0;
    pad->pressed_dpad_down = (trigger & 0x4) != 0;
    master = &HSD_PadMasterStatus[(u8)port];
    button = copy->button;
    pad->buttons = button;
    pad->a = (button & 0x100) != 0;
    pad->b = (button & 0x200) != 0;
    pad->l = (button & 0x40) != 0;
    pad->r = (button & 0x20) != 0;
    pad->x = (button & 0x400) != 0;
    pad->y = (button & 0x800) != 0;
    pad->z = (button & 0x10) != 0;
    pad->start = (button & 0x1000) != 0;
    pad->dpad_left = (button & 0x1) != 0;
    pad->dpad_right = (button & 0x2) != 0;
    pad->dpad_up = (button & 0x8) != 0;
    pad->dpad_down = (button & 0x4) != 0;
    pad->stick_x = master->nml_stickX;
    pad->stick_y = master->nml_stickY;
    pad->substick_x = master->nml_subStickX;
    pad->substick_y = master->nml_subStickY;
    pad->analog_l = master->nml_analogL;
    pad->analog_r = master->nml_analogR;
    pad->analog_a = master->nml_analogA;
    pad->analog_b = master->nml_analogB;
    x = pad->stick_x;
    y = pad->stick_y;
    ax = absf(x);
    ay = absf(y);
    PAD_STACK();
    if (ax < 0.2) {
        pad->stick_left = 0;
        pad->stick_right = 0;
    }
    if (ay < 0.2) {
        pad->stick_up = 0;
        pad->stick_down = 0;
    }
    if (x > 0.5) {
        pad->stick_right = 1;
        pad->stick_left = 0;
    }
    if (x < -0.5) {
        pad->stick_right = 0;
        pad->stick_left = 1;
    }
    if (y > 0.5) {
        pad->stick_up = 1;
        pad->stick_down = 0;
    }
    if (y < -0.5) {
        pad->stick_up = 0;
        pad->stick_down = 1;
    }
    flag = 0;
    if (pad->stick_right && !pad->last_stick_right)
        flag = 1;
    pad->pressed_stick_right = flag;
    flag = 0;
    if (pad->stick_left && !pad->last_stick_left)
        flag = 1;
    pad->pressed_stick_left = flag;
    flag = 0;
    if (pad->stick_up && !pad->last_stick_up)
        flag = 1;
    pad->pressed_stick_up = flag;
    flag = 0;
    if (pad->stick_down && !pad->last_stick_down)
        flag = 1;
    pad->pressed_stick_down = flag;
    pad->last_stick_right = pad->stick_right;
    pad->last_stick_left = pad->stick_left;
    pad->last_stick_up = pad->stick_up;
    pad->last_stick_down = pad->stick_down;
    pad->up = pad->dpad_up | pad->stick_up;
    pad->down = pad->dpad_down | pad->stick_down;
    pad->held_left = pad->dpad_left | pad->stick_left;
    pad->held_right = pad->dpad_right | pad->stick_right;
    pad->pressed_up = pad->pressed_dpad_up | pad->pressed_stick_up;
    pad->pressed_down = pad->pressed_dpad_down | pad->pressed_stick_down;
    pad->left = pad->pressed_dpad_left | pad->pressed_stick_left;
    pad->right = pad->pressed_dpad_right | pad->pressed_stick_right;
    if (pad->rumble != pad->previous_rumble) {
        if (pad->rumble != 0)
            HSD_PadRumbleOn(port);
        else
            HSD_PadRumbleOffN(port);
        pad->previous_rumble = pad->rumble;
    }
    reset = (pad->x && pad->b) && pad->start;
    if (reset) {
        pad->reset_hold_frames++;
        if (pad->reset_hold_frames > 30)
            TEA_HotReset(0);
    } else {
        pad->reset_hold_frames = 0;
    }
}
