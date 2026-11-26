#include "model_archive.h"

extern ModelArchive Ground;
extern s32 sDispClipOnOff;
extern void HSD_JObjDispAll(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);
extern void grdDispSub(HSD_JObj *joint);
extern void grdObjDispOpa(void);

void grdDisp(void)
{
    if (sDispClipOnOff == 0)
        HSD_JObjDispAll(Ground.models[0], 0, HSD_TRSP_OPA, 0);
    else
        grdDispSub(Ground.models[0]->child);
    grdObjDispOpa();
}
