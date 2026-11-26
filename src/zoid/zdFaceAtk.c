#include "zoid.h"
#include "ground_collision.h"

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

static inline GroundMask zdMaskB(void)
{
    GroundMask mask;

    mask = (GroundMask){{255, 0, 0, 0}};
    return mask;
}

static inline GroundMask zdMask(void)
{
    return zdMaskB();
}

s32 zdFaceAtk(ZoidState *zoid, f32 distance)
{
    Vec3 origin;
    Vec3 target;
    Vec3 *start;
    s32 unused[1];
    HSD_JObj *joint;

    joint = zoid->head_coobj.joint;
    if (joint == 0)
        joint = zoid->head_coobj.joint;
    if (joint == 0)
        joint = zoid->head_coobj.joint;
    if (joint == 0)
        joint = zoid->head_coobj.joint;
    if (joint == 0)
        return 0;
    start = &origin;
    start->x = zoid->camera_joint->matrix[0][3];
    target.x = start->x;
    start->y = zoid->camera_joint->matrix[1][3];
    target.y = start->y;
    start->z = zoid->camera_joint->matrix[2][3];
    target.z = start->z;
    target.x += distance * sinf(zoid->heading);
    target.z += distance * cosf(zoid->heading);
    if (sColPt(start, &target, zdMask()) == GROUND_NO_HIT)
        return 0;
    return 1;
}
