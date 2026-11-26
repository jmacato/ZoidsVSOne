#pragma readonly_strings on
#include "game_text.h"
#include "gx_tev.h"
#include "video.h"
#include "vi.h"

#define NULL 0

extern s32 sprintf(char *buffer, const char *format, ...);
extern void sMakeMatrix(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 HSD_JObjGetTranslationX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 1009, "jobj");
    return jobj->translation.x;
}

static const f64 text_pool_f64_0 = 0.0625;
static const f64 text_pool_f64_1 = 4503601774854144.0;
static const f64 text_pool_f64_2 = 4503599627370496.0;
static const f32 text_pool_f32_0 = 1.0F;
static const f32 text_pool_f32_1 = 15.0F;
static const f32 text_pool_f32_2 = 0.0625F;
static const f32 text_pool_f32_3 = 0.5F;
static const f32 text_pool_f32_4 = 1000.0F;
static const f32 text_pool_f32_5 = 24.0F;

void ascPrologue(void)
{
    char path[256];
    f32 *unused;
    s32 i;
    s32 k;
    HSD_JObj *joint;

    for (i = 0; i < ASC_FONT_COUNT; i++) {
        sprintf(path, "ascii/ascii%02d.dat", i);
        ascFile[i] = LoadArc2(path);
        if (ascFile[i] == 0)
            continue;
        joint = ascFile[i]->models[0];
        for (k = 0; k < ASC_GLYPH_MAX; k++) {
            ascH[i][k] = 0.0f;
        }
        if (joint != 0) {
            sMakeMatrix(joint);
            joint = joint ? joint->child : 0;
            k = 0;
            while (joint != 0) {
                ascH[i][k] = -HSD_JObjGetTranslationX(joint);
                joint = joint ? joint->next : 0;
                k++;
            }
        }
    }
    (void)text_pool_f64_0;
    (void)text_pool_f64_1;
    (void)text_pool_f64_2;
    (void)text_pool_f32_0;
    (void)text_pool_f32_1;
    (void)text_pool_f32_2;
    (void)text_pool_f32_3;
    (void)text_pool_f32_4;
    (void)text_pool_f32_5;
}


extern s32 sPutFontCamPrologue(void);
extern void sPutStringXYC2(char *text, GXColor color, GXColor shadow, s32 alpha, s32 flags, s32 align, f32 x,
                           f32 y, f32 z, f32 scale_x, f32 scale_y);
extern void HSD_StateInvalidate(s32 state);
extern void HSD_CObjEndCurrent(void);
extern void sPadAll(void);

void EndeFin(void)
{
    for (;;) {
        HSD_StartRender(HSD_RP_SCREEN);
        if (sPutFontCamPrologue() != 0) {
            sPutStringXYC2("B A T T L E  A L L  O V E R .", (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF },
                           (GXColor){ 0x00, 0x00, 0x32, 0x00 }, 0, 2, 3, 0.0f, 0.0f, -200.0f, 0.6f, 0.7f);
            sPutStringXYC2("Thank you for your playing!", (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF },
                           (GXColor){ 0x00, 0x00, 0x32, 0x00 }, 0, 2, 3, 0.0f, -50.0f, -250.0f, 0.6f, 0.7f);
            HSD_StateInvalidate(-1);
            HSD_CObjEndCurrent();
        }
        HSD_EndRender();
        HSD_VICopyXFB(HSD_RP_SCREEN);
        HSD_VISetXFBDrawDone();
        VIWaitForRetrace();
        sPadAll();
    }
}
