#include "types.h"

extern s16 TEA_SEVOL;
extern f64 __fabs(f64 x);
extern void HSD_AudioSFXPanning(u32 id, s8 pan);
extern void HSD_AudioSFXVolume(u32 id, u8 volume);
extern void HSD_AudioSFXSurroundPanning(u32 id, s8 pan);

static inline f64 fabs(f64 x)
{
    f64 r = __fabs(x);

    return r;
}

void TEA_SePosition(u32 id, s16 px, s16 pz)
{
    s32 x = px;
    s32 z = pz;
    s32 pan;
    s32 surround;
    s32 inside = 1;
    s32 volume;
    f32 vx;
    f32 vz;
    u8 level;
    f64 dx;
    f64 dz;
    s8 panning;
    s8 surround_panning;

    if (x > 500) {
        inside = 0;
    }
    if (z > 500) {
        inside = 0;
    }
    if (x < -500) {
        inside = 0;
    }
    if (z < -500) {
        inside = 0;
    }
    if (x > 500) {
        x = 500;
    }
    if (z > 500) {
        z = 500;
    }
    if (x < -500) {
        x = -500;
    }
    if (z < -500) {
        z = -500;
    }
    pan = x / 10 + 64;
    if (pan < 0) {
        pan = 0;
    }
    if (pan > 127) {
        pan = 127;
    }
    panning = pan;
    surround = 64 - z / 10;
    if (surround < 0) {
        surround = 0;
    }
    if (surround > 127) {
        surround = 127;
    }
    surround_panning = surround;
    dx = fabs(x);
    dz = fabs(z);
    vx = 128.0 * (500.0 - dx) / 500.0;
    vz = 128.0 * (500.0 - dz) / 500.0;
    if (vz > vx) {
        volume = vx;
    } else {
        volume = vz;
    }
    if (volume > 127) {
        volume = 127;
    }
    if (volume < 0) {
        volume = 0;
    }
    level = volume;
    if (inside == 0) {
        level = 0;
    }
    HSD_AudioSFXPanning(id, panning);
    HSD_AudioSFXVolume(id, level * TEA_SEVOL / 127);
    HSD_AudioSFXSurroundPanning(id, surround_panning);
}
