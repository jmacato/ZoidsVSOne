#include "game_zoid_data.h"

s32 ttl_ZoidChkWepPoint(s16 zoid, s16 point)
{
    s16 i;
    for (i = 0; i < 10; i++) {
        if (point == Tea_zoiddat[zoid].weapon_points[i])
            return 1;
    }
    return 0;
}
