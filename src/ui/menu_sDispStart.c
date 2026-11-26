#include "model_archive.h"

extern ModelArchive *menu1p;
extern s16 menumode;
extern s32 vsyncN;
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern void menu_sDispStartPushStart(void), menu_sDispStartPushLogo(void), menu_sDispZoidEmpireCountry(void);
extern void menu_sDispZoidBattleNewGameLoadGame(void), menu_sDispZoidBattleSingleTeamGame(void);
extern void menu_sDispZoidVSGame(void), menu_sDispStartMainMenu(void), menu_sDispStartMsgWin(void);
extern void menu_sDispStartWhiteInWhiteOut(void), debugmenudraw(void);

void menu_sDispStart(void)
{
    if (menu1p == 0)
        return;
    HSD_StartRender(0);
    if (HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        if (menumode != 0) {
            HSD_JObjDispAll(GetChild(menu1p->models[0], 0, -1, -1, -1, -1), 0, 7, 0);
            menu_sDispStartPushStart();
            menu_sDispStartPushLogo();
            menu_sDispZoidEmpireCountry();
            menu_sDispZoidBattleNewGameLoadGame();
            menu_sDispZoidBattleSingleTeamGame();
            menu_sDispZoidVSGame();
            menu_sDispStartMainMenu();
            if (menumode != 0 && menumode > 1)
                menu_sDispStartMsgWin();
        }
        menu_sDispStartWhiteInWhiteOut();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
