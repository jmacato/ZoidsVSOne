#include "ground_object.h"

extern GroundObject obj[50];
extern s32 objNow;
extern s32 grdCamChkObjR(HSD_JObj *joint);
extern void HSD_JObjDispAll(HSD_JObj *joint, void *mtx, u32 flags, u32 rendermode);

void grdObjDispXLU(void)
{
    s32 i;
    for (i = 0; i < objNow; i++) {
        if (obj[i].joint != 0 && grdCamChkObjR(obj[i].joint) != 0) {
            HSD_JObjDispAll(obj[i].joint, 0, HSD_TRSP_XLU, 0);
            HSD_JObjDispAll(obj[i].joint, 0, HSD_TRSP_TEXEDGE, 0);
        }
    }
}
