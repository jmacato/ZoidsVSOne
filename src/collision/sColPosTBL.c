#include "ground_collision.h"
extern u16 **grdcD2TBL;
u16 *sColPosTBL(Vec3 *point)
{
    return grdcD2TBL[sColPos(point)];
}
