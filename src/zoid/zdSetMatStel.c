#include "zoid.h"

extern void *steMobj;
extern void ZoidCopyMatSet(ZoidState *zoid, void *material);

void zdSetMatStel(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        ZoidCopyMatSet(zoid, steMobj);
    }
}
