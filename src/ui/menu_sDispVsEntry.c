#include "model_archive.h"

extern ModelArchive *menu_back1p, *menu1p;
extern s8 vsman;
extern s32 vsyncN;
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern void jobjDispAll(HSD_JObj *joint);
extern s32 jobjAnim(HSD_JObj *joint);
extern void selectcursolanm(s16 model);
extern void menu_sDispBattleFarmTitle(void), menu_sDispBattleFarmTitleSubButton(void);
extern void menu_sDispVsEntryPersonPartnerZoidPic(void), menu_sDispVsEntryPersonZoidStatus(void);
extern void menu_sDispVsFarmExitButton(void), menu_sDispVsEntryLoadButton(void);
extern void menu_sDispVsFarmPlayer1IconEnt(void), menu_sDispVsFarmPlayer2IconEnt(void);
extern void menu_sDispVsEntryPilotZoidList(void), menu_sDispVsEntryPersonPartnerZoidSelectFrame(void);
extern void menu_sDispYesNoMenu(void), debugmenudraw(void);

static inline s32 menuAnim(HSD_JObj *jobj)
{
    s32 done = jobjAnim(jobj);

    return done;
}

static inline HSD_JObj *menu1pModel(s32 i)
{
    HSD_JObj *jobj = menu1p->models[i];

    return jobj;
}

static inline HSD_JObj *menu_back1pModel(s32 i)
{
    HSD_JObj *jobj = menu_back1p->models[i];

    return jobj;
}

void menu_sDispVsEntry(void)
{
    HSD_StartRender(0);
    HSD_SetZSortMode(1, 1);
    if (menu_back1p != 0 && HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_back1p->lights);
        HSD_LObjSetupInit(menu_back1p->camera);
        GXSetCullMode(2);
        jobjDispAll(menu_back1pModel(0));
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
        menu_sDispVsEntryPersonPartnerZoidPic();
        menu_sDispVsEntryPersonZoidStatus();
        menu_sDispVsFarmExitButton();
        vsman = 0;
        menu_sDispVsEntryLoadButton();
        vsman = 1;
        menu_sDispVsEntryLoadButton();
        menu_sDispVsFarmPlayer1IconEnt();
        menu_sDispVsFarmPlayer2IconEnt();
        SetAnimArc2(menu1p, 9, 1);
        menuAnim(menu1pModel(9));
        vsman = 0;
        menu_sDispVsEntryPilotZoidList();
        vsman = 1;
        menu_sDispVsEntryPilotZoidList();
        vsman = 0;
        menu_sDispVsEntryPersonPartnerZoidSelectFrame();
        vsman = 1;
        menu_sDispVsEntryPersonPartnerZoidSelectFrame();
        vsman = 0;
        menu_sDispYesNoMenu();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
