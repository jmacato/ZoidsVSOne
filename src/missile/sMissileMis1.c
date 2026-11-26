#include "missile.h"

extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);
extern s32 sDivLineVn(Vec3 *a, Vec3 *b, s32 axis, f32 value, Vec3 *out);
extern void LoadArcAnimModel2(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 selected);

void sMissileMis1(Missile *missile, Missile *other)
{
    u8 top_padding[8];
    Vec3 end;
    Vec3 start;
    f32 radius;
    f64 limit;
    f32 (*inverse)[4];
    u8 frame_padding[8];

    if (other == 0)
        return;
    if (other->joint == 0)
        return;
    if (other->purge_timer != 0)
        return;
    radius = missile->step_length;
    inverse = missile->inverse;
    if (sLenJobj(missile->joint, other->joint) > radius + other->step_length)
        return;
    end.x = other->matrix[0][3];
    start.x = other->previous[0][3];
    end.y = other->matrix[1][3];
    start.y = other->previous[1][3];
    end.z = other->matrix[2][3];
    start.z = other->previous[2][3];
    PSMTXMultVec(inverse, &end, &end);
    PSMTXMultVec(inverse, &start, &start);
    limit = -(0.5 + radius);
    if (start.x < limit && end.x < limit)
        return;
    if (start.x > 0.5 && end.x > 0.5)
        return;
    if (start.x < limit && sDivLineVn(&start, &end, 0, limit, &start) == 0)
        return;
    if (end.x < limit && sDivLineVn(&start, &end, 0, limit, &end) == 0)
        return;
    if (start.x > 0.5 && sDivLineVn(&start, &end, 0, 0.5f, &start) == 0)
        return;
    if (end.x > 0.5 && sDivLineVn(&start, &end, 0, 0.5f, &end) == 0)
        return;
    if (start.z < -0.5 && end.z < -0.5)
        return;
    if (start.z > 0.5 && end.z > 0.5)
        return;
    if (start.z < -0.5 && sDivLineVn(&start, &end, 2, -0.5f, &start) == 0)
        return;
    if (end.z < -0.5 && sDivLineVn(&start, &end, 2, -0.5f, &end) == 0)
        return;
    if (start.z > 0.5 && sDivLineVn(&start, &end, 2, 0.5f, &start) == 0)
        return;
    if (end.z > 0.5 && sDivLineVn(&start, &end, 2, 0.5f, &end) == 0)
        return;
    if (start.x < limit && end.x < limit)
        return;
    if (start.x > 0.5 && end.x > 0.5)
        return;
    if (start.y < -0.5 && end.y < -0.5)
        return;
    if (start.y > 0.5 && end.y > 0.5)
        return;
    if (start.z < -0.5 && end.z < -0.5)
        return;
    if (start.z > 0.5 && end.z > 0.5)
        return;
    missile->hit = 1;
    sMissileSetAnim(missile, 1);
    LoadArcAnimModel2(missile->archive, missile->joint, 0, 1);
    sEffectSet(Tea_bulletdat[missile->bullet].hit_effect, 1, 0, missile->joint, 0);
    other->hit = 1;
    sMissileSetAnim(other, 1);
    LoadArcAnimModel2(other->archive, other->joint, 0, 1);
    sEffectSet(Tea_bulletdat[other->bullet].hit_effect, 1, 0, other->joint, 0);
}
