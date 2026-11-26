#include "game_camera.h"

extern CameraState *camTmp;
extern void GXGetProjectionv(f32 *projection);
extern void GXGetViewportv(f32 *viewport);
extern void HSD_CObjGetViewingMtx(void *cobj, f32 matrix[3][4]);
extern f32 (*HSD_CObjGetInvViewingMtxPtr(void *cobj))[4];
extern void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);

void sCameraMatrix(CameraState *camera)
{
    GXGetProjectionv(camera->projection);
    GXGetViewportv(camera->viewport);
    HSD_CObjGetViewingMtx(camTmp->cobj, camera->view);
    PSMTXCopy(HSD_CObjGetInvViewingMtxPtr(camTmp->cobj), camera->inverse_view);
}
