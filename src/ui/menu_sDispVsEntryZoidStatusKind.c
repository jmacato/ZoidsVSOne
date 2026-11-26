#include "model_archive.h"
#include "game_text.h"

extern ModelArchive *menu1p;
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjDispAll(HSD_JObj *joint);

static inline HSD_JObj *menuChild(s32 m, s32 a, s32 b, s32 c)
{
    HSD_JObj *ret = GetChild(menu1p->models[m], 0, a, b, c, -1);
    return ret;
}

void menu_sDispVsEntryZoidStatusKind(s32 player, s32 index, s32 value)
{
    s32 model = 6;
    char text[16];

    jobjDispAll(menuChild(model, player, index + 3, -1));
    sprintf(text, "%04d", value);
    putAscJobj(GetChild(menu1p->models[model], 0, player, index + 3, 0, -1), 2, text);
}
