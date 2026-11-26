#include "zoid.h"

void ZoidActDeath(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        zoid->death_pending = 1;
    }
}
