#include "weapon.h"
#include "game_part_data.h"

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

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

s32 sWeaponGetBarrel(WeaponState *weapon, Vec3 *out, f32 distance)
{
    s32 pad_top[1];
    s32 i;
    s32 bullet;
    s32 model;
    PartData *part;
    HSD_JObj *joint;
    f32 length;
    s32 bullets[2];
    s32 pad_mid[1];
    volatile f32 root;
    s32 unused[4];

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
        bullet = bullets[i & 1];
        length = sqrtf(joint->matrix[1][0] * joint->matrix[1][0] + joint->matrix[0][0] * joint->matrix[0][0] + joint->matrix[2][0] * joint->matrix[2][0], &root);
        out->x = distance * (joint->matrix[0][0] / length) + joint->matrix[0][3];
        out->y = distance * (joint->matrix[1][0] / length) + joint->matrix[1][3];
        out->z = distance * (joint->matrix[2][0] / length) + joint->matrix[2][3];
        break;
    }
    if (i == 12)
        return 0;
    return 1;
}
