#include "zoid.h"

extern void ZoidCopyMatRet(ZoidState *zoid);

void zdSetMatStelOFF(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        ZoidCopyMatRet(zoid);
    }
}
