#include "zoid.h"

void ZoidActDeadly(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        zoid->death_pending = 1;
    }
}
