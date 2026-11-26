#include "zoid.h"
#include "ground_collision.h"

extern f32 zdColPosY(f32 *point, u16 *selector);

void sSetRxRzB(ZoidState *zoid, HSD_JObj **front, HSD_JObj **back, f32 *rx, f32 *rz)
{
    u8 frame_padding[8];
    u16 selector;
    u8 unused[0x18];

    if (*front == 0) {
        return;
    }
    if (*back == 0) {
        return;
    }
    zdColPosY(zoid->position, &selector);
    *rx = 0.0f;
    *rz = 0.0f;
    if (selector != GROUND_POLYGON_NONE) {
        sColGetRxRz(&grdcNormal[grdcPolygon[selector].normal_index], zoid->heading, rx, rz);
    }
}
