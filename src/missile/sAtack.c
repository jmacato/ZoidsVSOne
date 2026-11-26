#include "joint.h"
#include "ground_collision.h"
#include "missile.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern f32 sLenPoint3d(Vec3 *first, Vec3 *second);
extern void sLinier3d(Vec3 *first, Vec3 *second);
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void LoadArcAnimModel2(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 animation);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY))
        result = 1;
    return result;
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void sAtack(Missile *missile)
{
    s32 i;
    Vec3 current;
    Vec3 previous;
    s32 pad1;
    Vec3 next;
    Vec3 hit;

    if (missile == NULL)
        return;
    missile->update_count++;
    if (missile->purge_timer != 0)
        return;
    if (missile->hit != 0)
        return;
    if (missile->kind == BULLET_KIND_GROUND && missile->update_count < 3)
        return;
    for (i = 0; i < 3; i++) {
        (&current.x)[i] = missile->matrix[i][3];
        (&previous.x)[i] = missile->previous[i][3];
    }
    missile->step_length = sLenPoint3d(&current, &previous);
    for (i = 0; i < 3; i++) {
        (&next.x)[i] = missile->matrix[i][3];
        (&hit.x)[i] = missile->previous[i][3];
    }
    if (GROUND_NO_HIT == sColPt(&hit, &next, (GroundMask){{255, 0, 0, 0}}))
        return;
    missile->hit_ground = 1;
    if (missile->kind != BULLET_KIND_GROUND)
        missile->hit = 1;
    sLinier3d(&hit, &next);
    for (i = 0; i < 3; i++) {
        missile->matrix[i][3] = (&hit.x)[i];
        missile->joint->matrix[i][3] = (&hit.x)[i];
    }
    HSD_JObjSetScaleX(missile->joint, 1.0f);
    sGlobal2Local(missile->joint);
    sMakeMatrix(missile->joint);
    if (missile->kind != BULLET_KIND_GROUND) {
        sMissileSetAnim(missile, 1);
        LoadArcAnimModel2(missile->archive, missile->joint, 0, 1);
        sEffectSet(Tea_bulletdat[missile->bullet].hit_effect, 1, 0, missile->joint, 0);
        return;
    }
    missile->speed = 0.0f;
}
