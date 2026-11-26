#include "model_archive.h"
#include "gx_tev.h"

extern ModelArchive *menu1p;
extern char menudispwinstr[180];
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 jobjAnim(HSD_JObj *joint);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern void sPutFontRect(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);

void menu_sDispStartMsgWin(void)
{
    char text[216];
    HSD_JObj *window;

    if (menu1p == 0)
        return;
    window = GetChild(menu1p->models[7], 0, -1, -1, -1, -1);
    SetAnimArc2(menu1p, 7, 1);
    jobjAnim(menu1p->models[7]);
    HSD_JObjDispAll(window, 0, 7, 0);
    if (menudispwinstr == 0)
        return;
    sprintf(text, "%s ", menudispwinstr);
    sPutFontRect(text, GetChild(menu1p->models[7], 0, 0, -1, -1, -1),
                 GetChild(menu1p->models[7], 0, 0, 0, -1, -1),
                 (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);
}
