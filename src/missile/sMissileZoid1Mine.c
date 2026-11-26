#include "zoid.h"
#include "missile.h"

#define NULL 0


extern s32 chk12(CoObj *object, HSD_JObj *target, f32 range);
extern f32 sColPosY(Vec3 *point, u16 *selector);
extern f32 sLenPoint3dR(Vec3 *point);
extern void ZoidCopyAnim(ZoidState *zoid);
extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

void sMissileZoid1Mine(Missile *missile, ZoidState *zoid)
{
    u8 top_padding[12];
    HSD_JObj *a1_joint;
    HSD_JObj *camera_joint;
    s32 hit_parts;
    f32 range;
    Vec3 position;
    Vec3 *offset;
    u8 frame_padding[36];

    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    camera_joint = zoid->camera_joint;
    if (camera_joint == 0)
        return;
    if (missile == 0)
        return;
    a1_joint = missile->a1_joint;
    if (a1_joint == 0)
        return;
    if (missile->update_count < 120)
        return;
    if ((s32)missile->hit_zoids[zoid->index] == 1)
        return;
    range = HSD_JObjGetScaleX(a1_joint);
    if (range < 0.2)
        return;
    position.x = camera_joint->matrix[0][3];
    position.y = camera_joint->matrix[1][3];
    position.z = camera_joint->matrix[2][3];
    position.y = sColPosY(&position, 0);
    range *= 0.5f;
    hit_parts = 0;
    if (chk12(&zoid->l_arm2_coobj, a1_joint, range))
        hit_parts |= 1;
    if (chk12(&zoid->l_arm1_coobj, a1_joint, range))
        hit_parts |= 2;
    if (chk12(&zoid->r_arm2_coobj, a1_joint, range))
        hit_parts |= 4;
    if (chk12(&zoid->r_arm1_coobj, a1_joint, range))
        hit_parts |= 8;
    if (chk12(&zoid->l_leg2_coobj, a1_joint, range))
        hit_parts |= 16;
    if (chk12(&zoid->l_leg1_coobj, a1_joint, range))
        hit_parts |= 32;
    if (chk12(&zoid->r_leg2_coobj, a1_joint, range))
        hit_parts |= 64;
    if (chk12(&zoid->r_leg1_coobj, a1_joint, range))
        hit_parts |= 128;
    if (chk12(&zoid->hip_coobj, a1_joint, range))
        hit_parts |= 128;
    if (hit_parts == 0)
        return;
    missile->hit_zoids[zoid->index] = 1;
    if (missile->hit == 0) {
        missile->hit = 1;
        sMissileSetAnim(missile, 1);
    }
    if (zoid->invulnerable_timer == 0) {
        ZoidCopyAnim(zoid);
        zoid->interpolation_remaining = 13;
        zoid->interpolation_duration = 15;
        offset = (Vec3 *)zoid->knockback;
        offset->x = camera_joint->matrix[0][3] - missile->matrix[0][0];
        offset->y = camera_joint->matrix[1][3] - missile->matrix[1][0];
        offset->z = camera_joint->matrix[2][3] - missile->matrix[2][0];
        (void)(sLenPoint3dR(offset) < 0.2 ? 0 : 0);
        zoid->health -= missile->damage;
        if (zoid->health < 0)
            zoid->health = 0;
        zoid->rumble_timer = 15;
    }
    sEffectSet(Tea_bulletdat[missile->bullet].hit_effect, 1, 0, missile->joint, 0);
}
