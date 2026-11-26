#include "model_archive.h"
#include "video.h"

extern ModelArchive *menu_saveloadp, *menu_saveloadbgp;
extern s32 vsyncN;
extern void OSReport(const char *fmt, ...);
extern void HSD_FogSet(struct HSD_Fog *fog);
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern void HSD_SetZSortMode(s32, s32);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void GXSetCullMode(s32);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjDispAll(HSD_JObj *joint);
extern void menu_sDispSaveLoadDataWindow(void), menu_sDispYesNoMenu(void), debugmenudraw(void);

void menu_sDispSaveLoad(void)
{
    s32 frame_padding[6];

    if (menu_saveloadp == 0) {
        OSReport("non menu_saveloadp\n");
        return;
    }
    HSD_FogSet(0);
    HSD_SetZSortMode(0, 0);
    HSD_VIData.current.vi.clear_clr = (GXColor){ 0, 0, 0, 0 };
    HSD_StartRender(0);
    if (HSD_CObjSetCurrent(menu_saveloadp->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_saveloadp->lights);
        HSD_LObjSetupInit(menu_saveloadp->camera);
        GXSetCullMode(0);
        if (menu_saveloadbgp != 0)
            jobjDispAll(GetChild(menu_saveloadbgp->models[0], -1, -1, -1, -1, -1));
        menu_sDispSaveLoadDataWindow();
        menu_sDispYesNoMenu();
        HSD_CObjEndCurrent();
    }
    HSD_EndRender();
    GXSetCullMode(2);
    debugmenudraw();
    vsyncN++;
}
