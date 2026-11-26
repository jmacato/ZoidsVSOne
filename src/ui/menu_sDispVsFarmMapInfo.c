#pragma readonly_strings on
#include "model_archive.h"
#include "game_mode.h"
#include "menu_message.h"
#include "gx_tev.h"

extern ModelArchive *menu1p;
extern ModelArchive *menu1p_map;
extern s32 sprintf(char *buffer, const char *format, ...);
extern char *GetMenuMsgAdr(s16 message);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjDisp(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void sPutFontRect(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);

void menu_sDispVsFarmMapInfo(void)
{
    s32 model = 10;
    char text[96];
    HSD_JObj *start;
    HSD_JObj *end;

    jobjDisp(GetChild(menu1p->models[model], 0, 0, -1, -1, -1));
    start = GetChild(menu1p->models[model], 0, 0, 0, -1, -1);
    end = GetChild(menu1p->models[model], 0, 0, 0, 0, -1);
    sprintf(text, "%s", GetMenuMsgAdr(GameMode.map + MENU_MSG_MAP_NAME_0));
    sPutFontRect(text, start, end, (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);
    jobjDisp(GetChild(menu1p->models[model], 0, 0, 0, -1, -1));
    jobjDisp(GetChild(menu1p->models[model], 0, 0, 2, -1, -1));
    if (menu1p_map != 0) {
        start = GetChild(menu1p->models[model], 0, 0, 1, -1, -1);
        end = GetChild(menu1p_map->models[0], 0, -1, -1, -1, -1);
        jobjCopyPos(start, end);
        jobjDispAll(end);
    }
}
