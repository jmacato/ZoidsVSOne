#include "zoid.h"
#include "missile.h"


extern f32 sMissileZoid1a(Missile *missile, CoObj *object, s32 push);
extern void ZoidCopyAnim(ZoidState *zoid);
extern s32 hitCalc2(ZoidState *attacker, s32 damage, ZoidState *zoid);
extern void OSReport(const char *format, ...);

s32 sMissileZoid1(Missile *missile, ZoidState *zoid)
{
    f32 t;
    f32 delta;
    f32 base;
    f32 rate;
    s32 damage;
    s32 health;
    s32 i;
    ZoidState *owner;

    if (zoid == 0)
        return 0;
    if (zoid->joint == 0)
        return 0;
    if (missile == 0)
        return 0;
    if (missile->update_count < 2)
        return 0;
    if (zoid == missile->owner && missile->update_count < 180)
        return 0;
    if (sMissileZoid1a(missile, &zoid->body_coobj, 0) == -1.0f)
        return 0;
    t = sMissileZoid1a(missile, &zoid->bust_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->bust_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->neck_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->hip_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->tail_coobjs[0], 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->tail_coobjs[1], 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->tail_coobjs[2], 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->head_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->l_arm1_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->r_arm1_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->l_arm2_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->r_arm2_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->l_leg1_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->r_leg1_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->l_leg2_coobj, 1);
    if (t == -1.0f)
        t = sMissileZoid1a(missile, &zoid->r_leg2_coobj, 1);
    if (t == -1.0f)
        return 0;
    for (i = 0; i < 3; i++) {
        base = missile->previous[i][3];
        delta = missile->matrix[i][3] - base;
        missile->matrix[i][3] = delta * t + base;
    }
    if (missile->hit == 0) {
        missile->hit = 1;
        sMissileSetAnim(missile, 1);
        sEffectSet(Tea_bulletdat[missile->bullet].hit_effect, 1, 0, missile->joint, 0);
    }
    owner = missile->owner;
    if (owner != 0 && owner->ai != 0) {
        owner->ai->missile_hit = owner->slot == zoid->slot ? 3 : 1;
    }
    if (zoid->invulnerable_timer == 0) {
        ZoidCopyAnim(zoid);
        zoid->interpolation_remaining = 13;
        zoid->interpolation_duration = 15;
        for (i = 0; i < 3; i++) {
            zoid->knockback[i] = 0.2 * missile->matrix[i][0];
        }

        damage = missile->damage;
        health = zoid->health;
        damage = hitCalc2(missile->owner, damage, zoid);
        OSReport("mis-dmg %d \n", damage);
        zoid->health -= damage;
        rate = (f32)damage / 100.0;
        if (rate > 1.0f)
            rate = 1.0f;
        zoid->position[0] += missile->matrix[0][0] * rate;
        zoid->position[2] += missile->matrix[2][0] * rate;
        if (damage > 0)
            zoid->health_bar_timer = 60;
        if (zoid->health < 0)
            zoid->health = 0;
        if (health != 0 && zoid->health == 0) {
            owner = missile->owner;
            if (owner != 0 && zoid->slot != owner->slot) {
                owner->kills++;
                owner->field_1BDC += zoid->max_health;
                if (missile->owner_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK)
                    owner->field_1BE0 += zoid->max_health;
            }
        }
        zoid->rumble_timer = 15;
    }
    return 1;
}
