#include "weapon.h"
#include "game_part_data.h"
#include "missile.h"

#define NULL 0

extern f64 __frsqrte(f64 value);
extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = x * guess;
        return *y;
    }
    return x;
}

static inline f32 sqrtf4(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;
    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

s32 sWeaponGetBarrelParabola(WeaponState *weapon, Vec3 *out, f32 distance)
{
    s32 i;
    s32 bullet;
    s32 model;
    PartData *part;
    HSD_JObj *joint;
    f32 length;
    f32 speed;
    f32 t;
    f32 drop;
    s32 pad_top[3];
    s32 bullets[2];
    Vec3 dir;
    s32 pad0;
    volatile f32 y2;
    volatile f32 y1;
    s32 unused[6];

    (void)&dir;
    if (weapon == 0)
        return 0;
    if (weapon->active == 0)
        return 0;
    model = weapon->model;
    part = Tea_partsdat;
    part += weapon->type;
    bullets[0] = part->bullets[0];
    bullets[1] = part->bullets[1];
    if (bullets[0] <= 0)
        return 0;
    if (bullets[1] <= 0)
        bullets[1] = bullets[0];
    if (weapon->archive->models[model] == 0)
        return 0;
    for (i = 0; i < 12; i++) {
        joint = weapon->barrels[i];
        if (joint == 0)
            continue;
        if (HSD_JObjGetScaleX(joint) < 0.2)
            continue;
        length = sqrtf(joint->matrix[1][0] * joint->matrix[1][0] + joint->matrix[0][0] * joint->matrix[0][0] + joint->matrix[2][0] * joint->matrix[2][0], &y1);
        bullet = bullets[i & 1];
        if (bullet < 0)
            continue;
        speed = 0.1 * Tea_bulletdat[bullet].speed;
        dir.x = joint->matrix[0][0] * speed / length;
        dir.y = joint->matrix[1][0] * speed / length;
        dir.z = joint->matrix[2][0] * speed / length;
        length = sqrtf4(dir.x * dir.x + dir.z * dir.z, &y2);
        if (0.0f == length)
            return 0;
        t = distance / length;
        drop = 1.0f + t;
        drop = 0.025 * (t * drop / 2.0f);
        out->x = t * dir.x + joint->matrix[0][3];
        out->y = t * dir.y + joint->matrix[1][3];
        out->z = t * dir.z + joint->matrix[2][3];
        out->y -= drop;
        break;
    }
    if (i == 12)
        return 0;
    return 1;
}
