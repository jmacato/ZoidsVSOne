#include "zoid.h"

extern void ZoidPutXZ(ZoidState *zoid);
extern void ZoidPutJumpingXZ(ZoidState *zoid);
extern void ZoidPutLandingXZ(ZoidState *zoid);

void ZoidAllPutXZ(void)
{
    s32 i;
    s64 frame_padding;

    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != 0) {
            s32 state = Zoid[i].jump_phase;
            s32 group = state & 0xF0;

            if (state == 0) {
                ZoidPutXZ(&Zoid[i]);
            } else if (state <= 3 && Zoid[i].forward_speed) {
                ZoidPutJumpingXZ(&Zoid[i]);
            } else if (group == 16) {
                ZoidPutJumpingXZ(&Zoid[i]);
            } else if (group == 32) {
                ZoidPutLandingXZ(&Zoid[i]);
            } else if (group == 48) {
                ZoidPutLandingXZ(&Zoid[i]);
            } else {
                ZoidPutLandingXZ(&Zoid[i]);
            }
        }
    }
}
