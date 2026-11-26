#include "model_archive.h"

extern ModelArchive *menu_back1p, *menu1p;
extern s16 menumode;
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
extern void menu_sDispBattleEntryPersonPartner(void), menu_sDispBattleEntryPersonPartnerZoidPic(void), menu_sDispBattleEntryPersonZoidStatus(void), menu_sDispBattleEntryPilotZoidList(void), menu_sDispBattleEntryPersonPartnerZoidSelectFrame(void), debugmenudraw(void);

void menu_sDispBattleEntry(void)
{
    HSD_StartRender(0);
    HSD_SetZSortMode(1, 1);
    if (HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
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
    if (HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        menu_sDispBattleFarmTitle();
        if (menumode != -1) {
            menu_sDispBattleFarmTitleSubButton();
            menu_sDispBattleEntryPersonPartner();
            menu_sDispBattleEntryPersonPartnerZoidPic();
            menu_sDispBattleEntryPersonZoidStatus();
            menu_sDispBattleEntryPilotZoidList();
            menu_sDispBattleEntryPersonPartnerZoidSelectFrame();
        }
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
