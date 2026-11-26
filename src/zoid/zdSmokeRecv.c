#include "zoid.h"

void zdSmokeRecv(ZoidState *zoid)
{
    u16 ally_smoke_timer;
    u16 enemy_smoke_timer;

    if (zoid != 0 && zoid->joint != 0) {
        ally_smoke_timer = zoid->ally_smoke_timer;
        if (ally_smoke_timer != 0) {
            zoid->ally_smoke_timer = ally_smoke_timer - 1;
        }
        enemy_smoke_timer = zoid->enemy_smoke_timer;
        if (enemy_smoke_timer != 0) {
            zoid->enemy_smoke_timer = enemy_smoke_timer - 1;
            zoid->target_pending = 0;
            zoid->ai->target_index = -1;
        }
    }
}
