#include "ground_collision.h"

extern u32 *grdcD2TBL;
extern u16 *grdcH2TBL;
extern s32 sprintf(char *buffer, const char *format, ...);
extern void *sReadFileU(char *name, s32 usb);

void sColPrologue(char *name, s32 usb)
{
    u8 frame_padding[8];
    char path[256];
    s32 x;
    s32 z;
    u32 *table;
    GroundColHeader *header;

    sColEpilogue();
    sprintf(path, "stage/%s", name);
    if ((grdcCol = header = sReadFileU(path, usb)) == 0)
        return;
    grdcPn = grdcCol->polygon_count;
    grdcVn = grdcCol->vertex_count;
    grdcMn = grdcCol->material_count;
    grdcNn = grdcCol->normal_count;
    grdcDivX = grdcCol->div_x;
    grdcDivZ = grdcCol->div_z;
    grdcStartX = grdcCol->start_x;
    grdcStartZ = grdcCol->start_z;
    grdcDiffX = grdcCol->diff_x;
    grdcDiffZ = grdcCol->diff_z;
    grdcEndX = grdcStartX + grdcDivX * grdcDiffX;
    grdcEndZ = grdcStartZ + grdcDivZ * grdcDiffZ;
    grdcMat = (GroundMask *)((u8 *)header + grdcCol->material_offset);
    grdcVtx = (Vec3 *)((u8 *)header + grdcCol->vertex_offset);
    grdcNormal = (Vec3 *)((u8 *)header + grdcCol->normal_offset);
    grdcPolygon = (GroundPolygon *)((u8 *)header + grdcCol->polygon_offset);
    grdcD2TBL = (u32 *)((u8 *)header + grdcCol->d2_offset);
    grdcH2TBL = (u16 *)((u8 *)header + grdcCol->h2_offset);
    table = grdcD2TBL;
    for (z = 0; z < grdcDivZ; z++) {
        for (x = 0; x < grdcDivX; x++) {
            u32 list_start = table[z * grdcDivX + x];
            if (list_start == 0xFFFFFFFF)
                grdcD2TBL[z * grdcDivX + x] = 0;
            else
                grdcD2TBL[z * grdcDivX + x] = (u32)(grdcH2TBL + list_start);
        }
    }
}
