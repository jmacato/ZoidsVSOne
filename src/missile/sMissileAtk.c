#include "weapon.h"
#include "missile.h"

extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern f32 sColCube4LineConnect(Vec3 *start, Vec3 *end);

s32 sMissileAtk(Missile *missile, WeaponInverse *target)
{
    Vec3 end;
    Vec3 start;
    f32 t;
    f32 delta;
    f32 base;
    f32 (*inverse)[4];
    s32 i;

    if (target == 0)
        return 0;
    if (target->joint == 0)
        return 0;
    inverse = target->inverse;
    for (i = 0; i < 3; i++) {
        (&end.x)[i] = missile->matrix[i][3];
        (&start.x)[i] = missile->previous[i][3];
    }
    PSMTXMultVec(inverse, &end, &end);
    PSMTXMultVec(inverse, &start, &start);
    if ((t = sColCube4LineConnect(&start, &end)) == -1.0f)
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
    return 1;
}
