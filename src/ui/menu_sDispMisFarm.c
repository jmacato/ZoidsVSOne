#include "model_archive.h"

extern ModelArchive *menu_back1p, *menu1p;
extern u8 menumodeanm[];
extern s32 vsyncN;
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void menu_sDispBattleFarmBack(void), menu_sDispBattleFarmZoid(void), menu_sDispBattleFarmWeapon(void);
extern void menu_sDispBattleFarmTitle(void), menu_sDispBattleFarmTitleSubButton(void);
extern void menu_sDispMisFarmModeButton(s32, s32), menu_sDispBattleFarmPersonZoidPartner(void);
extern void menu_sDispSaveLoadMenu(void), menu_sDispMsgWin(s16 model, s16 part);
extern void menu_sDispBattleFarmMsgWindowHelp(void), menu_sDispYesNoMenu(void), debugmenudraw(void);

void menu_sDispMisFarm(void)
{
    HSD_StartRender(0);
    HSD_SetZSortMode(1, 1);
    if (menu_back1p != 0 && HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_back1p->lights);
        HSD_LObjSetupInit(menu_back1p->camera);
        GXSetCullMode(2);
        menu_sDispBattleFarmBack();
        menu_sDispBattleFarmZoid();
        menu_sDispBattleFarmWeapon();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_SetZSortMode(0, 0);
    if (menumodeanm[0] != 0 && menu1p != 0 && HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        menu_sDispBattleFarmTitle();
        menu_sDispBattleFarmTitleSubButton();
        menu_sDispMisFarmModeButton(0, 0);
        menu_sDispBattleFarmPersonZoidPartner();
        menu_sDispSaveLoadMenu();
        menu_sDispMsgWin(3, 1);
        menu_sDispBattleFarmMsgWindowHelp();
        menu_sDispYesNoMenu();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
