#pragma readonly_strings on
#include "model_archive.h"
#include "game_save.h"
#include "game_text.h"

extern ModelArchive *menu1p;
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

void menu_sDispBattleShopHaveBp(void)
{
    s16 model = 18;
    char text[12];
    s32 frame_padding;

    HSD_JObjDispAll(GetChild(menu1p->models[model], 0, 0, -1, -1, -1), 0, 7, 0);
    {
        s32 *money = &IveSave[0].money;

        if (*money > 999999)
            sprintf(text, "999999");
        else
            sprintf(text, "%6d", *money);
    }
    putAscJobj(GetChild(menu1p->models[model], 0, 0, 1, -1, -1), 4, text);
}
