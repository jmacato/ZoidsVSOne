#include "gx_texture_types.h"

s32 calc_doltexture_size(u32 format, s32 width, s32 height)
{
    switch (format) {
    case GX_TF_I4:
    case GX_TF_C4:
    case GX_TF_CMPR:
        return ((width + 7) & ~7) / 2 * ((height + 7) & ~7);
    case GX_TF_I8:
    case GX_TF_IA4:
    case GX_TF_C8:
        return ((width + 7) & ~7) * ((height + 3) & ~3);
    case GX_TF_IA8:
    case GX_TF_RGB565:
    case GX_TF_RGB5A3:
    case GX_TF_C14X2:
        return ((width + 3) & ~3) * ((height + 3) & ~3) * 2;
    case GX_TF_RGBA8:
        return ((width + 3) & ~3) * ((height + 3) & ~3) * 4;
    default:
        return 0;
    }
}
