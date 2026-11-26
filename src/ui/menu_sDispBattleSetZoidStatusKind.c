#include "model_archive.h"
#include "game_text.h"

extern ModelArchive *menu1p;
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);

void menu_sDispBattleSetZoidStatusKind(s32 index, s32 value)
{
    char text[16];
    s32 model = 9;

    sprintf(text, "%04d", value);
    putAscJobj(GetChild(menu1p->models[model], 0, 6, index + 1, 0, -1), 2, text);
}
