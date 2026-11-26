#include "zoid.h"

s32 hitCalc2(ZoidState *attacker, s32 damage, ZoidState *target)
{
    if (attacker == 0)
        return damage;
    if (target == 0)
        return damage;
    if (attacker->joint == 0)
        return damage;
    if (target->joint == 0)
        return damage;
    damage -= target->armor;
    if (damage < 10)
        damage = 10;
    return damage;
}
