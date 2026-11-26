#include "zoid.h"
#include "missile.h"

extern s32 sChkCubeInSphere(f32 (*cube)[4], f32 (*sphere)[4]);

s32 zdWpCoAtk(CoObj *object, ZoidAttackObject *target, s32 kind)
{
    s32 hit;
    Vec3 position;
    u8 frame_padding[0x8];
    CoObj *co = object;
    ZoidAttackObject *attack = target;
    s32 effect = kind;

    if (co == 0) {
        return 0;
    }
    if (co->joint == 0) {
        return 0;
    }
    if (attack == 0) {
        return 0;
    }
    if (attack->joint == 0) {
        return 0;
    }
    {
        f32 (*inverse)[4] = attack->inverse;
        hit = sChkCubeInSphere(co->joint->matrix, inverse);
    }
    if (hit == 0) {
        return 0;
    }
    if (effect != -1) {
        position.x = (co->joint->matrix[0][3] + attack->joint->matrix[0][3]) / 2.0f;
        position.y = (co->joint->matrix[1][3] + attack->joint->matrix[1][3]) / 2.0f;
        position.z = (co->joint->matrix[2][3] + attack->joint->matrix[2][3]) / 2.0f;
        sEffectSet(effect, 0, &position.x, 0, 0);
    }
    co->health -= 10;
    if (co->health < 0) {
        co->health = 0;
    }
    co->field_5C = 1;
    return hit;
}

s32 ZoidWpCoAtk(ZoidAttackObject *attack, ZoidState *zoid, s32 effect)
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
    if (zdWpCoAtk(&zoid->head_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdWpCoAtk(&zoid->neck_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdWpCoAtk(&zoid->bust_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdWpCoAtk(&zoid->hip_coobj, attack, effect) != 0) {
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (zdWpCoAtk(&zoid->tail_coobjs[i], attack, effect) != 0) {
            return 1;
        }
    }
    if (zdWpCoAtk(&zoid->l_arm1_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdWpCoAtk(&zoid->r_arm1_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdWpCoAtk(&zoid->l_leg1_coobj, attack, effect) != 0) {
        return 1;
    }
    if (zdWpCoAtk(&zoid->r_leg1_coobj, attack, effect) != 0) {
        return 1;
    }
    return 0;
}
