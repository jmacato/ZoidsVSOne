#include "zoid.h"

s32 hitCalc(ZoidState *attacker, s32 damage, ZoidState *defender)
{
    if (attacker == 0)
        return damage;
    if (defender == 0)
        return damage;
    if (attacker->joint == 0)
        return damage;
    if (defender->joint == 0)
        return damage;
    damage += attacker->melee_power_bonus;
    damage -= defender->armor;
    if (damage < 10)
        damage = 10;
    return damage;
}
