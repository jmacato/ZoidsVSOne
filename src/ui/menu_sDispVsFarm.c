#include "model_archive.h"

extern ModelArchive *menu_back1p, *menu1p;
extern s32 vsyncN;
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void jobjDispAll(HSD_JObj *joint);
extern void menu_sDispBattleFarmTitle(void), menu_sDispBattleFarmTitleSubButton(void);
extern void menu_sDispVsEntryPersonPartnerZoidPic(void), menu_sDispVsEntryPersonZoidStatus(void);
extern void menu_sDispVsFarmEntryButton(void), menu_sDispVsFarmStageButton(void);
extern void menu_sDispVsFarmBattleButton(void), menu_sDispVsFarmMapInfo(void);
extern void menu_sDispVsFarmPlayer1Icon(void), menu_sDispVsFarmPlayer2Icon(void);
extern void menu_sDispYesNoMenu(void), debugmenudraw(void);

void menu_sDispVsFarm(void)
{
    HSD_StartRender(0);
    HSD_SetZSortMode(1, 1);
    if (menu_back1p != 0 && HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_back1p->lights);
        HSD_LObjSetupInit(menu_back1p->camera);
        GXSetCullMode(2);
        jobjDispAll(menu_back1p->models[0]);
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
        menu_sDispVsEntryPersonPartnerZoidPic();
        menu_sDispVsEntryPersonZoidStatus();
        menu_sDispVsFarmEntryButton();
        menu_sDispVsFarmStageButton();
        menu_sDispVsFarmBattleButton();
        menu_sDispVsFarmMapInfo();
        menu_sDispVsFarmPlayer1Icon();
        menu_sDispVsFarmPlayer2Icon();
        menu_sDispYesNoMenu();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
