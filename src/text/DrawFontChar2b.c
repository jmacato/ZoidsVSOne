#include "os_font.h"
#include "gx_state.h"
#include "gx_geometry.h"

extern OSFontHeader *FontData;
extern s16 FontSize;

static inline void GXPosition3f32(f32 x, f32 y, f32 z)
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXTexCoord2s16(s16 s, s16 t)
{
    GXWGFifo.s16 = s;
    GXWGFifo.s16 = t;
}

void DrawFontChar2b(s32 s, s32 t, s32 width, f32 x, f32 y, f32 z, f32 scale)
{
    s16 s1;
    s16 t1;
    s16 s2;
    s16 t2;
    f32 x2;
    f32 y2;
    f32 w;
    f32 h;

    s1 = s;
    t1 = t;
    s2 = s + width;
    w = width;
    x2 = x + w * scale;
    h = FontData->cellHeight * FontSize / 16 / FontData->cellWidth;
    y2 = y - scale * h;

    t2 = t + FontData->cellHeight;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x, y, z);
    GXTexCoord2s16(s1, t1);
    GXPosition3f32(x2, y, z);
    GXTexCoord2s16(s2, t1);
    GXPosition3f32(x2, y2, z);
    GXTexCoord2s16(s2, t2);
    GXPosition3f32(x, y2, z);
    GXTexCoord2s16(s1, t2);
}
