#include "zoid.h"

extern u32 zdsMotTBL[];
extern void ZoidWalkSpeed(ZoidState *zoid);

void ZoidWalkSumuSpd(ZoidState *zoid)
{
    ZoidControlData *control;
    f32 maximum;
    s32 locked;

    if (zoid != 0 && zoid->joint != 0) {
        control = zoid->control;
        if (control == 0) {
            return;
        }
        zoid->max_speed = control->base_max_speed + zoid->speed_bonus;
        maximum = (f64)control->field_009C / 100.0;
        if (zoid->booster_on == 0) {
            maximum = (f64)zoid->max_speed / 100.0;
        }
        if (zoid->field_1A74 > maximum) {
            zoid->field_1A74 = maximum;
        }
        if (zoid->field_1A74 < (f64)-control->max_reverse_speed / 100.0) {
            zoid->field_1A74 = (f64)-control->max_reverse_speed / 100.0;
        }
        if (zoid->ramped_speed != zoid->field_1A74) {
            if (zoid->ramped_speed > zoid->field_1A74) {
                zoid->ramped_speed -= (f32)control->deceleration / 10000.0;
                if (zoid->ramped_speed < zoid->field_1A74) {
                    zoid->ramped_speed = zoid->field_1A74;
                }
            }
            if (zoid->ramped_speed < zoid->field_1A74) {
                zoid->ramped_speed += (f32)control->acceleration / 10000.0;
                if (zoid->ramped_speed > zoid->field_1A74) {
                    zoid->ramped_speed = zoid->field_1A74;
                }
            }
        }
        locked = 0;
        if ((zdsMotTBL[zoid->current_animation] & 1) != 0) {
            locked = 1;
        }
        if (locked != 0 && zoid->animation_stopped != 0) {
            locked = 0;
        }
        if (locked == 0) {
            ZoidWalkSpeed(zoid);
        }
    }
}
