#include "zoid.h"

extern void zdStelON(ZoidState *zoid);
extern void zdStelOFF(ZoidState *zoid);
extern void zdTrans1(ZoidState *zoid);
extern void zdSetMatStelOFF(ZoidState *zoid);
extern void zdSetMatStel(ZoidState *zoid);
extern void ZoidTrans(ZoidState *zoid, f32 transformation);
extern void ZoidCopyMatRet(ZoidState *zoid);

void ZoidTransMode(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != 0) {
            s32 state;
            s32 previous;

            if (Zoid[i].option_active != 0) {
                zdStelON(&Zoid[i]);
            } else {
                zdStelOFF(&Zoid[i]);
            }
            state = Zoid[i].stel_state;
            previous = Zoid[i].previous_stel_state;
            if (previous == state) {
                if (state == ZOID_STEL_FADING) {
                    zdTrans1(&Zoid[i]);
                }
            } else {
                if (previous == ZOID_STEL_ON) {
                    zdSetMatStelOFF(&Zoid[i]);
                }
                if (previous == ZOID_STEL_FADING) {
                    ZoidTrans(&Zoid[i], 1.0f);
                }
                ZoidCopyMatRet(&Zoid[i]);
                if (state == ZOID_STEL_FADING) {
                    zdTrans1(&Zoid[i]);
                }
                if (state == ZOID_STEL_ON) {
                    zdSetMatStel(&Zoid[i]);
                }
                Zoid[i].previous_stel_state = state;
            }
        }
    }
}
