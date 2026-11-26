#include "missile.h"
#include "lobj.h"


void sMissileLight(void)
{
    s32 i;
    s32 count = 0;
    Missile *missile = missileStart;
    s32 show;
    u8 frame_padding[8];

    for (i = 0; i < 200; i++, missile++) {
        if (missile == 0) {
            return;
        }
        if (missile->purge_timer == 0 && missile->joint != 0) {
            show = 1;
            if (missile->kind == BULLET_KIND_GROUND && missile->hit == 0) {
                show = 0;
            }
            if (missile->kind == BULLET_KIND_FLOAT) {
                show = 0;
            }
            count++;
            if (count >= 3) {
                show = 0;
            }
            if (show != 0) {
                HSD_LObjAddCurrent(missile->light);
            }
        }
    }
}
