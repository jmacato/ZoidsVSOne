#include "model_archive.h"

extern ModelArchive Ground;
extern s32 sDispClipOnOff;
extern void HSD_JObjDispAll(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);
extern void grdDispSubXLU(HSD_JObj *joint);
extern void grdObjDispXLU(void);

void grdDispXLU(void)
{
    if (sDispClipOnOff == 0) {
        HSD_JObjDispAll(Ground.models[0], 0, HSD_TRSP_XLU, 0);
        HSD_JObjDispAll(Ground.models[0], 0, HSD_TRSP_TEXEDGE, 0);
    } else {
        grdDispSubXLU(Ground.models[0]->child);
    }
    grdObjDispXLU();
}
