#include "zoid.h"
void zdOptionUseOK(ZoidState *zoid)
{
    s32 motion = zoid->current_animation;
    if (zoid->option_type == ZOID_OPTION_SHIELD && motion == 6)
        zoid->option_use_state = 0;
}
