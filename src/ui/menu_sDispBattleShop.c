#include "model_archive.h"

extern ModelArchive *menu_back1p, *menu1p;
extern s32 vsyncN;
extern void putErr(char *message);
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void menu_sDispMsgWin(s16 model, s16 part);
extern void menu_sDispBattleFarmBack(void), menu_sDispBattleFarmZoid(void), menu_sDispBattleFarmWeapon(void);
extern void menu_sDispBattleFarmTitle(void), menu_sDispBattleFarmTitleSubButton(void);
extern void menu_sDispYesNoMenu(void), debugmenudraw(void);

extern void menu_sDispBattleShopHaveListDsip(void), menu_sDispBattleShopLButtonAnimZoidWepOptSub(void);
extern void menu_sDispBattleShopunfold(void), menu_sDispBattleShopLButton(void);
extern void menu_sDispBattleShopLButtonZoidWepOptSub(void), menu_sDispBattleShopHaveBp(void);
extern void menu_sDispBattleShopZoidHaveZoidList(void), menu_sDispBattleShopHavePartsList(void);
extern void menu_sDispBattleMsgArea(void);

void menu_sDispBattleShop(void)
{
    HSD_StartRender(0);
    HSD_SetZSortMode(1, 1);
    if (menu_back1p == 0)
        putErr("out of memory. menu back shop");
    if (menu1p == 0)
        putErr("out of memory. menu 1 shop");
    if (menu_back1p != 0 && HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_back1p->lights);
        HSD_LObjSetupInit(menu_back1p->camera);
        GXSetCullMode(0);
        menu_sDispBattleFarmBack();
        menu_sDispBattleFarmZoid();
        menu_sDispBattleFarmWeapon();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_SetZSortMode(0, 0);
    if (menu1p != 0 && HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        menu_sDispBattleFarmTitle();
        menu_sDispBattleFarmTitleSubButton();
        menu_sDispBattleShopHaveListDsip();
        menu_sDispBattleShopLButtonAnimZoidWepOptSub();
        menu_sDispBattleShopunfold();
        menu_sDispBattleShopLButton();
        menu_sDispBattleShopLButtonZoidWepOptSub();
        menu_sDispBattleShopHaveBp();
        menu_sDispBattleShopZoidHaveZoidList();
        menu_sDispBattleShopHavePartsList();
        menu_sDispMsgWin(3, 1);
        menu_sDispBattleMsgArea();
        menu_sDispYesNoMenu();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
}
