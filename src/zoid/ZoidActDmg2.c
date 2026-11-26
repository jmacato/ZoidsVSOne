#include "zoid.h"

extern void ZoidInertia(ZoidState *zoid);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void PartnerFace(s32 face, s32 frames);
extern void zdChgNormal(ZoidState *zoid);
extern void zdLinierTm(ZoidState *zoid, s32 frames);

void ZoidActDmg2(ZoidState *zoid)
{
    s32 motions[6] = {43, 44, 45, 46, 47, 48};

    ZoidInertia(zoid);
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, motions[zoid->action - ZOID_ACTION_DMG2_1]);
        zoid->action_phase = 1;
        if (Zoid[2].joint != 0 && zoid == &Zoid[2] && zoid->slot == 0) {
            PartnerFace(4, 60);
        }
        break;
    case 1:
        if (zoid->animation_stopped == 0 && zoid->animation_looped == 0) {
            break;
        }
    default:
        zdChgNormal(zoid);
        zdLinierTm(zoid, 60);
        break;
    }
}
