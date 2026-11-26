#include "model_archive.h"
#include "game_text.h"

extern ModelArchive *menu1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjDispAll(HSD_JObj *joint);
extern int sprintf(char *buf, const char *fmt, ...);

static inline HSD_JObj *menuChild(s32 m, s32 a, s32 b, s32 c)
{
    HSD_JObj *ret = GetChild(menu1p->models[m], 0, a, b, c, -1);
    return ret;
}

void menu_sDispBattleEntryZoidStatusKind(s32 group, s32 kind, s32 value)
{
    s32 idx = 6;
    char buf[60];

    jobjDispAll(menuChild(idx, group, kind + 3, -1));
    sprintf(buf, "%04d", value);
    putAscJobjLR(menuChild(idx, group, kind + 3, 3), 0, buf, 1);
}
