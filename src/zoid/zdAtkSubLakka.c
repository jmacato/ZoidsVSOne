#include "zoid.h"

extern s32 zdLakkaTest2(ZoidState *zoid);
extern void setAnimRateXor(HSD_JObj *joint, f32 rate, HSD_JObj *excluded);
extern void ZoidInertia(ZoidState *zoid);

s32 zdAtkSubLakka(ZoidState *zoid)
{
    f32 lift;
    s32 frame_padding[4];

    if (zoid->control->field_00F8 == 1) {
        return 0;
    }
    if ((zoid->movement_flags & 1) == 0 && zoid->grounded == 0) {
        zoid->displacement[1] -= 0.025;
        zoid->position[1] += zoid->displacement[1];
    }
    if (zdLakkaTest2(zoid) == 0) {
        return 0;
    }
    setAnimRateXor(zoid->joint, 0.0f, zoid->animation_exclusion);
    zoid->displacement[0] = zoid->body_coobj.movement[0];
    zoid->displacement[1] = zoid->body_coobj.movement[1];
    zoid->displacement[2] = zoid->body_coobj.movement[2];
    ZoidInertia(zoid);
    lift = zoid->height_offset;
    zoid->position[1] += lift;
    zoid->height_offset -= lift;
    zoid->unsupported_frames = 0;
    return 1;
}
