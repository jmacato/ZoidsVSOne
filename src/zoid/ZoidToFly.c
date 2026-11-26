#include "zoid.h"

extern void ZoidTo(ZoidState *zoid, ZoidLimb *limb, s32 flag);
extern void ZoidToF(ZoidLimb *limb, ZoidLimb *target, f32 rate);
extern void ZoidToDownF(ZoidLimb *limb, ZoidLimb *target, f32 rate);

void ZoidToFly(ZoidState *zoid)
{
    s32 flag;
    f32 rate = 0.1f;
    s32 i;

    flag = zoid->action >= ZOID_ACTION_ATTACK_0 && zoid->action <= ZOID_ACTION_ATTACK_9;
    if (flag != 0) {
        rate = 1.0f;
    }
    ZoidTo(zoid, &zoid->limbs[8], flag);
    if (zoid->death_pending != 0) {
        ZoidToDownF(&zoid->limbs[1], &zoid->limbs[8], rate);
    } else {
        ZoidToF(&zoid->limbs[1], &zoid->limbs[8], rate);
    }
    for (i = 2; i < 8; i++) {
        if (zoid->death_pending != 0) {
            ZoidToDownF(&zoid->limbs[i], &zoid->limbs[i - 1], rate);
        } else {
            ZoidToF(&zoid->limbs[i], &zoid->limbs[i - 1], rate);
        }
    }
}
