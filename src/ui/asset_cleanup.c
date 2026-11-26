#include "model_archive.h"

extern HSD_JObj *dspJobjEx3[2];
extern ModelArchive *dspRader, *dsp1p, *dspPartner, *dspPoint, *dspPos00;
extern ModelArchive *menu1p, *menu_back1p, *menu_saveloadbgp, *menu_saveloadp;
extern s32 menuretno;
extern void jobjUnrefAll(HSD_JObj *joint);
extern void HSD_VIWaitEFBFlush(void);
extern void sDispPurgePartsWarn(void), sDispPurgePartsPause(void), sDispPurgePartsBP(void);
extern void sDispPurgePartsContinue(void), sDispPurgePartsMessage(void);

s32 menufncZoidBattleEnd(void)
{
    if (menu1p != 0)
        PurgeArc2(menu1p);
    menu1p = 0;
    if (menu_back1p != 0)
        PurgeArc2(menu_back1p);
    menu_back1p = 0;
    return menuretno;
}

void ttlMenuPurgeSaveLoad(void)
{
    if (menu_saveloadbgp != 0) {
        PurgeArc2(menu_saveloadbgp);
        menu_saveloadbgp = 0;
    }
    if (menu_saveloadp != 0) {
        PurgeArc2(menu_saveloadp);
        menu_saveloadp = 0;
    }
    HSD_VIWaitEFBFlush();
}
