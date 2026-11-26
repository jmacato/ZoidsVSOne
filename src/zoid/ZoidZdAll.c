#include "zoid.h"
#include "weapon.h"
#include "game_part_data.h"
#include "game_zoid_data.h"

extern void __assert(const char *file, u32 line, const char *condition);
extern s32 ZoidZdCoAtack(ZoidAttackObject *attack, ZoidState *zoid, s32 effect);
extern void ZoidCoAtackDmg(ZoidState *zoid, ZoidAttackObject *attack, ZoidState *target);
extern s32 ZoidWpCoAtk(ZoidAttackObject *attack, ZoidState *zoid, s32 effect);
extern void ZoidCoWpAtackDmg(WeaponState *weapon, WeaponInverse *inverse, ZoidState *zoid);
extern s32 ZoidZdCoObj(ZoidState *zoid, ZoidState *other);
extern void zdCoCoMinR(ZoidState *zoid, ZoidState *other);
extern void ZoidCopyAnim(ZoidState *zoid);

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == 0) {
        __assert("jobj.h", 899, "jobj");
    }
    return jobj->scale.x;
}

void ZoidZdAll(void)
{
    s32 weapon_effect;
    s32 attack_index;
    s32 type;
    s32 i;
    s32 j;
    s32 k;
    ZoidAttackObject *attack;
    s32 unused[2];
    ZoidState *zoid;
    s32 team;
    s32 hit;
    HSD_JObj *jobj;
    s32 attack_effect;
    ZoidState *other;
    WeaponState *weapon;
    f32 range;

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        hit = 0;
        if (zoid->joint == 0) {
            continue;
        }
        attack_index = -1;
        type = zoid->type;
        if (zoid->action >= ZOID_ACTION_ATTACK_0 && zoid->action <= ZOID_ACTION_ATTACK_9) {
            attack_index = zoid->action - ZOID_ACTION_ATTACK_0;
        }
        if (zoid->jump_phase != 0 && zoid->jump_attack_phase != 0) {
            attack_index = 5;
        }
        if (attack_index != -1) {
            attack_effect = Tea_zoiddat[type].attack_hit_effects[attack_index];
        } else {
            attack_effect = Tea_zoiddat[type].attack_hit_effects[0];
        }
        for (j = 0; j < 16; j++) {
            other = &Zoid[j];
            if (i == j || zoid->contact[j] == 0 || other->joint == 0 || other->invulnerable_timer != 0) {
                continue;
            }
            for (k = 0; k < 10; k++) {
                attack = &zoid->attack_objects[k];
                if (attack == 0 || attack->joint == 0) {
                    continue;
                }
                if ((s8)attack->touched[j] != 0) {
                    continue;
                }
                if (attack->joint->scale.x <= 0.1 || attack->joint->scale.y <= 0.1 || attack->joint->scale.z <= 0.1) {
                    continue;
                }
                hit = ZoidZdCoAtack(attack, other, attack_effect);
                if (hit != 0) {
                    attack->touched[j] = 1;
                    ZoidCoAtackDmg(zoid, attack, other);
                }
            }
            if (hit != 0) {
                break;
            }
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == 0) {
            continue;
        }
        hit = 0;
        for (j = 0; j < 100; j++) {
            weapon = &sWeapon[j];
            if (weapon->active == 0 || weapon->owner == zoid) {
                continue;
            }
            for (k = 0; k < 12; k++) {
                jobj = weapon->inverses[k].joint;
                weapon_effect = Tea_partsdat[weapon->type].hit_effect;
                if (jobj == 0) {
                    continue;
                }
                if (HSD_JObjGetScaleX(jobj) < 0.1) {
                    continue;
                }
                hit = ZoidWpCoAtk((ZoidAttackObject *)&weapon->inverses[k], zoid, weapon_effect);
                if (hit != 0) {
                    ZoidCoWpAtackDmg(weapon, &weapon->inverses[k], zoid);
                    break;
                }
            }
            if (hit != 0) {
                break;
            }
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == 0) {
            continue;
        }
        for (j = i; j < 16; j++) {
            other = &Zoid[j];
            if (i == j || zoid->contact[j] == 0 || other->joint == 0) {
                continue;
            }
            if (ZoidZdCoObj(zoid, other) == 0) {
                continue;
            }
            zdCoCoMinR(zoid, other);
            ZoidCopyAnim(zoid);
            ZoidCopyAnim(other);
            zoid->interpolation_remaining = 10;
            zoid->interpolation_duration = 15;
            other->interpolation_remaining = 10;
            other->interpolation_duration = 15;
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == 0) {
            continue;
        }
        range = zoid->search_range;
        for (j = 0; j < 16; j++) {
            zoid->target_visibility[j] = 0;
            if (i == j || Zoid[j].joint == 0) {
                continue;
            }
            if (zoid->slot == Zoid[j].slot) {
                zoid->target_visibility[j] = 1;
            } else if (!(range < zoid->distances[j]) && Zoid[j].stel_state != ZOID_STEL_ON && zoid->enemy_smoke_timer == 0) {
                zoid->target_visibility[j] = 1;
            }
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint == 0) {
            continue;
        }
        team = zoid->slot;
        if (zoid->enemy_smoke_timer != 0) {
            continue;
        }
        for (j = 0; j < 16; j++) {
            if (i == j || zoid->target_visibility[j] == 0) {
                continue;
            }
            for (k = 0; k < 16; k++) {
                other = &Zoid[k];
                if (i != k && j != k && team == other->slot) {
                    other->target_visibility[j] = 1;
                }
            }
        }
    }

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != 0 && zoid->target_pending != 0 && zoid->target_visibility[zoid->target_slot] == 0) {
            zoid->target_pending = 0;
        }
    }
}
