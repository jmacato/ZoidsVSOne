#include "zoid.h"

void zdAtack1(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        zoid->requested_action = ZOID_ACTION_ATTACK_0;
    }
}
