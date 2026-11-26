#include "gx_tev.h"
#include "joint.h"
#include "os_font.h"
#include "cobj.h"

extern void *LastSheet;
/* by value to match (the definition takes GXColor *; pointers drop the stack copies) */
extern void sPutFontRectPrologue(GXColor color, GXColor shadow, s32 alpha, u32 flags);
extern void sPutFontRectEpilogue(void);
extern void DrawFontChar00(char *string, HSD_JObj *joint, f32 scale);

void sPutFontRect(char *string, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor *color, GXColor *shadow,
                  s32 alpha, u32 flags)
{
    s32 width;
    void *image;
    s32 s;
    s32 t;
    Vec3 eye;
    char *p;
    s32 widest;
    s32 line_width;
    s32 height;
    f32 scale_x;
    f32 scale_y;
    f32 scale;

    widest = 0;
    height = 0;
    line_width = 0;
    LastSheet = 0;
    p = string;
    while (*p != 0) {
        if (*p == '\n') {
            p++;
        } else if (*p == '\r') {
            line_width = 0;
            p++;
            height += 24;
        } else {
            p = OSGetFontTexture(p, &image, &s, &t, &width);
            line_width += width;
            if (widest < line_width)
                widest = line_width;
        }
    }
    if (widest != 0) {
        scale_x = (bottom_right->matrix[0][3] - top_left->matrix[0][3]) / (f32)widest;
        scale_y = (top_left->matrix[1][3] - bottom_right->matrix[1][3]) / (f32)(height + 24);
        scale = scale_x;
        if (scale_x > scale_y)
            scale = scale_y;
        sPutFontRectPrologue(*color, *shadow, alpha, flags);
        HSD_CObjGetEyePosition(HSD_CObjGetCurrent(), &eye);
        DrawFontChar00(string, top_left, scale);
        sPutFontRectEpilogue();
    }
}
