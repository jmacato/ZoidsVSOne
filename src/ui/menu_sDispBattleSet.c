#include "model_archive.h"

extern ModelArchive *menu_back1p, *menu1p;
extern s16 menumode;
extern void putErr(char *message);
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void selectcursolanm(s16 model);
extern void menu_sDispMsgWin(s16 model, s16 part);
extern void menu_sDispBattleFarmBack(void), menu_sDispBattleFarmZoid(void), menu_sDispBattleFarmWeapon(void);
extern void menufnczoidmountpointdisp(void);
extern void menu_sDispBattleFarmTitle(void), menu_sDispBattleFarmTitleSubButton(void);
extern void menu_sDispBattleSetunfold(void), menu_sDispBattleSetLButton(void), menu_sDispBattleSetZoidStatus(void);
extern void menu_sDispBattleSetZoidHaveZoidList(void), menu_sDispBattleSetequipPartsList(void);
extern void menu_sDispBattleSetequipParts(void), menu_sDispBattleSetHavePartsList(void);
extern void menu_sDispYesNoMenu(void), debugmenudraw(void);

void menu_sDispBattleSet(void)
{
    if (menu_back1p == 0)
        putErr("out of memory. menu back error");
    HSD_StartRender(0);
    HSD_SetZSortMode(1, 1);
    if (menu_back1p != 0 && HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_back1p->lights);
        HSD_LObjSetupInit(menu_back1p->camera);
        GXSetCullMode(2);
        menu_sDispBattleFarmBack();
        menu_sDispBattleFarmZoid();
        menu_sDispBattleFarmWeapon();
        if (menumode == 4 || menumode == 7)
            menufnczoidmountpointdisp();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_SetZSortMode(0, 0);
    if (menu1p != 0 && HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        selectcursolanm(7);
        menu_sDispBattleFarmTitle();
        menu_sDispBattleFarmTitleSubButton();
        menu_sDispBattleSetunfold();
        menu_sDispBattleSetLButton();
        menu_sDispBattleSetZoidStatus();
        menu_sDispBattleSetZoidHaveZoidList();
        menu_sDispBattleSetequipPartsList();
        menu_sDispBattleSetequipParts();
        menu_sDispBattleSetHavePartsList();
        menu_sDispMsgWin(3, 0);
        menu_sDispYesNoMenu();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
}
