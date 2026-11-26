#pragma readonly_strings on
#include "game_pad.h"
#include "model_archive.h"

extern char menudispyesnostr1[180], menudispyesnostr2[180];
extern PadState *sPad1, *sPad2;
extern char *strcpy(char *destination, const char *source);
extern void SeSelectB(void);
extern u32 TXT_Menu[];
extern char TXT_Menu_dat[];
extern ModelArchive *menu_yesnop;
extern s32 vsyncN;
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void menu_sDispYesNoMenu(void), debugmenudraw(void);

void SetMenuMsgAdr(s16 message, char *destination)
{
    /* The original routine leaves this sentinel unchanged. */
    static s16 nn = -2;
    if (message != nn) {
        if (message == -1)
            strcpy(destination, " ");
        else
            strcpy(destination, TXT_Menu_dat + TXT_Menu[message]);
    }
}

s32 menuYesNo(s32 selected, const char *first, const char *second)
{
    strcpy(menudispyesnostr1, first);
    strcpy(menudispyesnostr2, second);
    if (sPad1->left != 0 || sPad2->left != 0) {
        SeSelectB();
        return 1;
    }
    if (sPad1->right != 0 || sPad2->right != 0) {
        SeSelectB();
        return 0;
    }
    return selected;
}

void menuYesNoSetStr(const char *first, const char *second)
{
    strcpy(menudispyesnostr1, first);
    strcpy(menudispyesnostr2, second);
}

void menu_sDispStartYesNo(void)
{
    HSD_StartRender(0);
    HSD_SetZSortMode(0, 0);
    if (HSD_CObjSetCurrent(menu_yesnop->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_yesnop->lights);
        HSD_LObjSetupInit(menu_yesnop->camera);
        GXSetCullMode(0);
        menu_sDispYesNoMenu();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
