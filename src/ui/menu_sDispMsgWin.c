#include "model_archive.h"
#include "gx_tev.h"

extern ModelArchive *menu1p;
extern char menudispwinstr[180];
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern void sPutFontRect(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);

void menu_sDispMsgWin(s16 model, s16 part)
{
    char text[208];
    HSD_JObj *start;
    HSD_JObj *end;

    if (menu1p == 0)
        return;
    HSD_JObjDisp(GetChild(menu1p->models[model], 0, part, -1, -1, -1), 0, 7, 0);
    if (menudispwinstr == 0)
        return;
    sprintf(text, "%s ", menudispwinstr);
    start = GetChild(menu1p->models[model], 0, part, 0, -1, -1);
    end = GetChild(menu1p->models[model], 0, part, 1, -1, -1);
    sPutFontRect(text, start, end, (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);
}
