#include "zoid.h"

extern s32 zdZdCoAtk(CoObj *co, ZoidAttackObject *attack, s32 effect);

s32 ZoidZdCoAtack(ZoidAttackObject *attack, ZoidState *zoid, s32 effect)
{
    s32 i;

    if (attack == 0) {
        return 0;
    }
    if (attack->joint == 0) {
        return 0;
    }
    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    if (zdZdCoAtk(&zoid->head_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdZdCoAtk(&zoid->neck_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdZdCoAtk(&zoid->bust_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdZdCoAtk(&zoid->hip_coobj, attack, effect) != 0) {
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (zdZdCoAtk(&zoid->tail_coobjs[i], attack, effect) != 0) {
            return 1;
        }
    }
    if (zdZdCoAtk(&zoid->l_arm1_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdZdCoAtk(&zoid->r_arm1_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdZdCoAtk(&zoid->l_leg1_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdZdCoAtk(&zoid->r_leg1_coobj, attack, effect) != 0) {
        return 1;
    }
    return 0;
}
