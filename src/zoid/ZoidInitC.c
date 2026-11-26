#include "zoid.h"

extern s32 ZoidInit_(ZoidState *zoid, s32 type, s32 flags);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void jobjAnim(HSD_JObj *joint);
extern void OSReport(const char *format, ...);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);

s32 ZoidInitC(ZoidState *zoid, s32 type, s32 color)
{
    if (ZoidInit_(zoid, type, 0) == 0) {
        return 0;
    }
    ZoidSetAnim(zoid, 103);
    jobjAnim(zoid->joint);
    OSReport("zd color =%d \n", color);
    return ZoidColor(zoid, color, 0);
}
