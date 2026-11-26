#include "game_text.h"
#include "model_archive.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY))
        result = 1;
    return result;
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void jobjDisp(HSD_JObj *joint);

f32 putAscLR_sp(Vec3 *position, s32 font, char *text, s32 right_align, f32 spacing)
{
    f32 *widths;
    HSD_JObj *root;
    HSD_JObj *child;
    f32 width;
    f32 total;
    s32 glyph;
    f32 x;
    f32 y;
    f32 z;

    if (font < 0 || font >= ASC_FONT_COUNT)
        return 0.0f;
    if (ascFile[font] == 0)
        return 0.0f;
    root = ascFile[font]->models[0];
    if (root == 0)
        return 0.0f;
    if (right_align != 0)
        position->x -= getAscH_sp(font, text, spacing);
    total = 0.0f;
    widths = ascH[font];
    while (*text != 0) {
        glyph = getAscNum(text);
        if (glyph >= ASC_GLYPH_MAX)
            glyph = -1;
        if (glyph != -1) {
            width = widths[glyph];
            child = GetChild(root, 0, glyph, -1, -1, -1);
            if (child != 0) {
                x = position->x;
                child->matrix[0][3] = x;
                y = position->y;
                child->matrix[1][3] = y;
                z = position->z;
                child->matrix[2][3] = z;
                sGlobal2Local(child);
                HSD_JObjSetMtxDirty(child);
                jobjDisp(child);
                total += width;
                position->x += width;
            }
            total += spacing;
        }
        if (isKanji(*text))
            text += 2;
        else
            text += 1;
    }
    return total;
}
