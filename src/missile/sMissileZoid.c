#include "weapon.h"
#include "zoid.h"
#include "missile.h"

#define NULL 0

extern void __assert(const char *file, s32 line, const char *expr);
extern void sMissileZoid1Smoke(Missile *missile, ZoidState *zoid);
extern void sMissileZoid1Mine(Missile *missile, ZoidState *zoid);
extern s32 sMissileZoid1(Missile *missile, ZoidState *zoid);
extern s32 sMissileAtk(Missile *missile, WeaponInverse *target);
extern void sMissileMis1(Missile *missile, Missile *other);

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

void sMissileZoid(void)
{
    Missile *missile = missileStart;
    s32 i;
    s32 j;
    WeaponState *weapon;
    ZoidState *owner;
    s32 k;
    HSD_JObj *joint;
    u8 frame_padding[8];

    for (i = 0; i < 200; i++, missile++) {
        if (missile == 0)
            return;
        if (!(missile->flags & MISSILE_FLAG_ACTIVE))
            continue;
        if (missile->purge_timer != 0)
            continue;
        if (missile->zoid_hit != MISSILE_ZOID_HIT_MINE && missile->hit != 0)
            continue;
        if (missile->joint == 0)
            continue;
        if (missile->field_30 != 0)
            continue;
        switch (missile->zoid_hit) {
        case MISSILE_ZOID_HIT_SMOKE:
            for (j = 0; j < 16; j++) {
                sMissileZoid1Smoke(missile, &Zoid[j]);
            }
            break;
        case MISSILE_ZOID_HIT_MINE:
            for (j = 0; j < 16; j++) {
                sMissileZoid1Mine(missile, &Zoid[j]);
            }
            break;
        default:
            for (j = 0; j < 16; j++) {
                if (sMissileZoid1(missile, &Zoid[j]) != 0)
                    break;
            }
            for (j = 0; j < 100; j++) {
                weapon = &sWeapon[j];
                owner = weapon->owner;
                if (weapon->active == 0)
                    continue;
                for (k = 0; k < 12; k++) {
                    joint = weapon->inverses[k].joint;
                    if (joint == 0)
                        continue;
                    if (HSD_JObjGetScaleX(joint) < 0.8)
                        continue;
                    if (sMissileAtk(missile, &weapon->inverses[k]) == 0)
                        continue;
                    if (weapon->drain != 0 && owner != 0 && owner->option_type == ZOID_OPTION_SHIELD) {
                        owner->option_energy -= 200;
                        if (owner->option_energy < 0)
                            owner->option_energy = 0;
                    }
                    break;
                }
            }
            break;
        }
        if (missile->target_missile != 0)
            sMissileMis1(missile, missile->target_missile);
    }
}
