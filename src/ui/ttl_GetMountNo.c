#include "game_zoid_data.h"

s16 ttl_GetMountNo(s16 zoid, s16 slot)
{
    return Tea_zoiddat[zoid].mount[slot];
}
