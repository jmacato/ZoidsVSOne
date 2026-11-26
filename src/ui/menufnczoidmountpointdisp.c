#include "zoid.h"
#include "game_save.h"

extern s8 menuZoidMountPointDsip[10];
extern s16 ttl_GetMountNo(s16 zoid, s16 slot);
extern void zdDispCursorSet(ZoidState *zoid, s32 mount, s32 enable);

void menufnczoidmountpointdisp(void)
{
    s16 i;
    s16 count;
    s16 mount;

    count = 0;
    for (i = 0; i < 10; i++) {
        if (menuZoidMountPointDsip[i] == 1) {
            count++;
            mount = ttl_GetMountNo(IveSave[0].selected_zoid, i);
            zdDispCursorSet(&Zoid[0], mount, 1);
        }
    }
    if (count == 0) {
        for (i = 0; i < 28; i++)
            zdDispCursorSet(&Zoid[0], i, 0);
    }
}
