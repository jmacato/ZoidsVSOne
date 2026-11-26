#include "zoid.h"

extern void ZoidWalkSumuSpd(ZoidState *zoid);
extern void ZoidWalkSusumu(ZoidState *zoid);

void ZoidWalk(ZoidState *zoid)
{
    ZoidWalkSumuSpd(zoid);
    ZoidWalkSusumu(zoid);
}
