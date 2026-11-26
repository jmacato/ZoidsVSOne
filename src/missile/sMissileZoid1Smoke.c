#include "zoid.h"
#include "missile.h"

#define NULL 0

extern void __assert(const char *file, s32 line, const char *expr);
extern f32 sLenJobj(HSD_JObj *a, HSD_JObj *b);

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

void sMissileZoid1Smoke(Missile *missile, ZoidState *zoid)
{
    s32 slot;
    HSD_JObj *a1_joint;
    HSD_JObj *camera_joint;
    ZoidState *owner;
    f32 scale;

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
    owner = missile->owner;
    if (a1_joint == 0)
        return;
    slot = -1;
    if (owner != 0)
        slot = owner->slot;
    if (missile->update_count < 2)
        return;
    if (zoid == owner && missile->update_count < 180)
        return;
    scale = HSD_JObjGetScaleX(a1_joint);
    if (scale < 0.8)
        return;
    if (2.0f * sLenJobj(a1_joint, camera_joint) > scale)
        return;
    if (zoid->slot == slot)
        zoid->ally_smoke_timer = 60;
    else
        zoid->enemy_smoke_timer = 180;
}
