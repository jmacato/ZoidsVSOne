#include "weapon.h"
#include "zoid.h"
#include "game_part_data.h"
#include "missile.h"

#define NULL 0

extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

static inline void sWeaponGetBullets(s32 *bullets, s32 type)
{
    bullets[0] = Tea_partsdat[type].bullets[0];
    bullets[1] = Tea_partsdat[type].bullets[1];
}

void sWeaponFire(WeaponState *weapon)
{
    s32 i;
    HSD_JObj *joint;
    s32 bullet;
    s32 extra_damage;
    s32 k;
    s32 effect;
    WeaponMarker *marker;
    ZoidState *owner;
    s32 model;
    s32 type;
    s32 bullets[2];
    u8 frame_padding[4];

    if (weapon == 0)
        return;
    if (weapon->active == 0)
        return;
    model = weapon->model;
    type = weapon->type;
    if (type <= 0)
        return;
    sWeaponGetBullets(bullets, type);
    if (bullets[0] <= 0)
        return;
    if (bullets[1] <= 0)
        bullets[1] = bullets[0];
    if (weapon->archive->models[model] == 0)
        return;
    if (weapon->flags & 4)
        return;
    if (weapon->state_flags & WEAPON_STATE_STOPPED)
        return;
    owner = weapon->owner;
    if (owner->death_started != 0) {
        weapon->flags |= WEAPON_FLAG_LOOP_OFF;
        return;
    }
    extra_damage = Tea_partsdat[type].power;
    if (owner != 0)
        extra_damage += owner->bullet_power_bonus;
    for (i = 0; i < 12; i++) {
        joint = weapon->barrels[i];
        if (joint == 0)
            continue;
        if (HSD_JObjGetScaleX(joint) < 1.0)
            continue;
        if (weapon->ammo == 0)
            continue;
        weapon->ammo--;
        bullet = bullets[i & 1];
        effect = Tea_bulletdat[bullet].fire_effect;
        if (effect > 0)
            sEffectSet(effect, 1, 0, joint, 0);
        if (weapon->bullet_kind != BULLET_KIND_AT20) {
            owner = weapon->owner;
            sMissileFire(owner, owner->target_pending != 0 ? &Zoid[owner->target_slot] : 0, 0, joint->matrix, bullet, extra_damage);
        } else {
            for (k = 0; k < 20; k++) {
                weapon->marker_cursor++;
                if (weapon->marker_cursor >= weapon->marker_count)
                    weapon->marker_cursor = 0;
                marker = &weapon->markers[weapon->marker_cursor];
                if (marker->joint != 0)
                    break;
            }
            if (k != 20)
                sMissileFire(weapon->owner, marker->target, marker->source, joint->matrix, bullet, extra_damage);
            else
                sMissileFire(weapon->owner, 0, 0, joint->matrix, bullet, extra_damage);
        }
    }
}
