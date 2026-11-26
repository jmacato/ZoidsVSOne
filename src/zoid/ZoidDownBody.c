#include "zoid.h"
#include "ground_collision.h"

extern f32 zdColPosY(f32 *point, u16 *selector);
extern f32 zdDownBody(ZoidState *zoid, CoObj *co);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sLinier3d(Vec3 *current, Vec3 *target, f32 fraction);

static inline GroundMask zdGroundMask(void)
{
    GroundMask a;
    GroundMask b;
    GroundMask c;
    GroundMask d;

    a = (GroundMask){{255, 0, 0, 0}};
    b = a;
    c = b;
    d = c;
    return d;
}

void ZoidDownBody(ZoidState *zoid)
{
    Vec3 *pb;
    Vec3 pos;
    u8 unused0[4];
    f32 sum;
    Vec3 joint;
    Vec3 base;
    u8 unused1[4];
    f32 y;
    Vec3 delta;
    Vec3 *pj;
    ZoidControlData *control;
    s32 hit;

    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    control = zoid->control;
    if (zoid->death_pending == 0)
        return;
    y = zoid->position[1];
    if (y > zdColPosY(zoid->position, 0)) {
        zoid->displacement[1] -= 0.025;
        zoid->position[1] += zoid->displacement[1];
    }
    sum = 0.0f;
    sum += zdDownBody(zoid, &zoid->head_coobj);
    sum += zdDownBody(zoid, &zoid->neck_coobj);
    sum += zdDownBody(zoid, &zoid->bust_coobj);
    sum += zdDownBody(zoid, &zoid->hip_coobj);
    sum += zdDownBody(zoid, &zoid->l_arm1_coobj);
    sum += zdDownBody(zoid, &zoid->r_arm1_coobj);
    sum += zdDownBody(zoid, &zoid->l_leg1_coobj);
    sum += zdDownBody(zoid, &zoid->r_leg1_coobj);
    sum += zdDownBody(zoid, &zoid->l_arm2_coobj);
    sum += zdDownBody(zoid, &zoid->r_arm2_coobj);
    sum += zdDownBody(zoid, &zoid->l_leg2_coobj);
    sum += zdDownBody(zoid, &zoid->r_leg2_coobj);
    sum += zdDownBody(zoid, &zoid->tail_coobjs[0]);
    sum += zdDownBody(zoid, &zoid->tail_coobjs[1]);
    if (zoid->death_started == 0)
        zoid->position[1] += sum / 28.0f;
    sMakeMatrix(zoid->joint);
    pos.x = zoid->camera_joint->matrix[0][3];
    pos.y = zoid->camera_joint->matrix[1][3];
    pos.z = zoid->camera_joint->matrix[2][3];
    y = zdColPosY(&pos.x, 0) - (pos.y - 0.7);
    if (y > 0.0f)
        zoid->height_offset += y;
    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    joint.x = zoid->sweep_joint->matrix[0][3];
    base.x = zoid->sweep_origin[0];
    joint.y = zoid->sweep_joint->matrix[1][3];
    base.y = zoid->sweep_origin[1];
    joint.z = zoid->sweep_joint->matrix[2][3];
    base.z = zoid->sweep_origin[2];
    pb = &base;
    pj = &joint;
    hit = 0;
    y = sColPt(pb, pj, (GroundMask){{255, 0, 0, 0}});
    if (GROUND_NO_HIT != y) {
        sLinier3d(pb, pj, y);
        hit = 1;
    }
    if (control->sweep_radius > 0) {
        if (GROUND_NO_HIT != sColPtR(&base, (Vec3 *)zoid->sweep_origin, zdGroundMask(), control->sweep_radius / 100.0))
            hit = 1;
    }
    if (hit != 0) {
        delta.x = joint.x - base.x;
        zoid->position[0] -= delta.x;
        delta.y = joint.y - base.y;
        zoid->position[1] -= delta.y;
        delta.z = joint.z - base.z;
        zoid->position[2] -= delta.z;
        (void)&delta;
        zoid->sweep_hit = 1;
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
    }
}
