#include "zoid.h"
#include "game_zoid_data.h"

extern f32 sLenPoint3d(Vec3 *first, Vec3 *second);

void zdAtkSubForPullLen(ZoidState *zoid, s32 attack)
{
    s8 slot;
    ZoidState *target;
    ZoidControlData *control;
    f32 rate;
    f32 range;
    f32 length;
    f32 scale;

    if (zoid != 0 && zoid->joint != 0) {
        zoid->pull_scale = 1.0f;
        slot = zoid->attack_target;
        if (slot != -1 && (target = &Zoid[slot])->joint != 0) {
            rate = 1.0f;
            control = zoid->control;
            if (Tea_zoiddat[zoid->type].attack_pull[attack] != 0) {
                range = Tea_zoiddat[zoid->type].attack_ranges[attack];
                if (0.0f != (f32)Tea_zoiddat[zoid->type].attack_ranges[attack]) {
                    range += (f32)control->pull_range_offset / 10.0;
                    if (0.0f != range) {
                        length = sLenPoint3d((Vec3 *)zoid->position, (Vec3 *)target->position);
                        if (length < 1.0f)
                            length = 1.0f;
                        rate = length / range;
                    }
                }
            }
            if (rate > 1.0f)
                rate = 1.0f;
            if (rate < 0.2)
                rate = 0.2f;
            scale = zoid->pull_scale;
            if (rate < scale) {
                scale = scale - 0.1;
                if (rate > scale)
                    scale = rate;
            }
            if (rate > scale) {
                scale += 0.03;
                if (rate < scale)
                    scale = rate;
            }
            zoid->pull_scale = scale;
        }
    }
}
