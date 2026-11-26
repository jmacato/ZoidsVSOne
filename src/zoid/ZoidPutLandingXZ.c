#include "zoid.h"
#include "ground_collision.h"


extern f32 zdGetBasePoly(ZoidState *zoid, f32 *point);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ik3d(ZoidState *zoid, FootJoint *foot);

void ZoidPutLandingXZ(ZoidState *zoid)
{
    f32 y;
    f32 low;
    f32 ground;
    u8 frame_padding[8];
    f32 rx;
    f32 rz;
    u8 unused[16];
    f32 dx;
    f32 dz;
    u16 selector;
    s32 count;
    ZoidControlData *control;

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    control = zoid->control;
    y = zdGetBasePoly(zoid, zoid->position);
    selector = zoid->ground_polygon;
    count = 0;
    zoid->ground_height = y;
    low = y;
    if (control->field_00F4 != 2) {
        if (zoid->feet[0].joint != 0) {
            ground = zoid->feet[0].ground;
            if (zoid->feet[0].flags & FOOT_FLAG_SUPPORTED) {
                count++;
            }
            if (low > ground) {
                low = ground;
            }
        }
        if (zoid->feet[1].joint != 0) {
            ground = zoid->feet[1].ground;
            if (zoid->feet[1].flags & FOOT_FLAG_SUPPORTED) {
                count++;
            }
            if (low > ground) {
                low = ground;
            }
        }
    }
    if (zoid->feet[2].joint != 0) {
        ground = zoid->feet[2].ground;
        if (zoid->feet[2].flags & FOOT_FLAG_SUPPORTED) {
            count++;
        }
        if (low > ground) {
            low = ground;
        }
    }
    if (zoid->feet[3].joint != 0) {
        if (zoid->feet[3].flags & FOOT_FLAG_SUPPORTED) {
            count++;
        }
        if (low > zoid->feet[3].ground) {
            low = zoid->feet[3].ground;
        }
    }
    rx = 0.0f;
    rz = 0.0f;
    if (selector != GROUND_POLYGON_NONE) {
        sColGetRxRz(&grdcNormal[grdcPolygon[selector].normal_index], zoid->heading, &rx, &rz);
    }
    dx = rx - zoid->ground_rx;
    dz = rz - zoid->ground_rz;
    if (dx < 0.5235987666666666) {
        if (dx > 0.01) {
            dx = 0.01f;
        }
    } else {
        dx = 0.1f;
    }
    if (dx > -0.5235987666666666) {
        if (dx < -0.01) {
            dx = -0.01f;
        }
    } else {
        dx = -0.1f;
    }
    zoid->ground_rx += dx;
    zoid->ground_rz += dz;
    if (zoid->position[1] < low - 1.0f) {
        zoid->position[1] = low - 1.0f;
    }
    if (zoid->position[1] < y) {
        zoid->height_offset += zoid->position[1] - y;
        zoid->position[1] = y;
        if (zoid->height_offset < -0.1) {
            zoid->height_offset += 0.01;
        }
    }
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    zoid->ground_normal_count = 0;
    zoid->ground_normal_sum[0] = 0.0f;
    zoid->ground_normal_sum[1] = 0.0f;
    zoid->ground_normal_sum[2] = 0.0f;
    if (control->field_00F4 != 2) {
        ik3d(zoid, &zoid->feet[0]);
        ik3d(zoid, &zoid->feet[1]);
    }
    ik3d(zoid, &zoid->feet[2]);
    ik3d(zoid, &zoid->feet[3]);
    zoid->foot_contacts = count;
    if (count != 0) {
        if ((zoid->jump_phase & 0xF0) == 32) {
            zoid->jump_phase = 48;
            zoid->field_1B24 = 60;
        }
    }
}
