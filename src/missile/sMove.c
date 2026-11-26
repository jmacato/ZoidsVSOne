#include "missile.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
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

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

extern s32 TEA_VidChk(s32 id);
extern s32 sAObjAnimeAll(HSD_JObj *joint);
extern u32 PSMTXInverse(f32 src[3][4], f32 inv[3][4]);
extern void misProc(Missile *missile);
extern void HSD_LObjSetPosition(void *lobj, Vec3 *position);

void sMove(Missile *missile)
{
    f32 step[3];
    u8 mid_padding[24];
    Vec3 position;
    s32 k;
    u8 frame_padding[40];

    if (missile == 0)
        return;
    missile->update_count++;
    if (missile->purge_timer != 0)
        return;
    if (missile->hit != 0)
        return;
    if (missile->se >= 0 && missile->se_playing != 0 && TEA_VidChk(missile->se_voice) == 0)
        missile->se_playing = 0;
    missile->previous[0][0] = missile->matrix[0][0];
    missile->previous[0][1] = missile->matrix[0][1];
    missile->previous[0][2] = missile->matrix[0][2];
    missile->previous[0][3] = missile->matrix[0][3];
    missile->previous[1][0] = missile->matrix[1][0];
    missile->previous[1][1] = missile->matrix[1][1];
    missile->previous[1][2] = missile->matrix[1][2];
    missile->previous[1][3] = missile->matrix[1][3];
    missile->previous[2][0] = missile->matrix[2][0];
    missile->previous[2][1] = missile->matrix[2][1];
    missile->previous[2][2] = missile->matrix[2][2];
    missile->previous[2][3] = missile->matrix[2][3];
    if (sAObjAnimeAll(missile->joint) != 0) {
        if (missile->animation == 0)
            sMissileSetAnim(missile, 1);
        else
            missile->purge_timer = 1;
    }
    if (missile->kind != BULLET_KIND_GROUND && missile->hit_ground != 0)
        missile->speed = 0.0f;
    for (k = 0; k < 3; k++) {
        step[k] = missile->matrix[k][0] * missile->speed;
        missile->matrix[k][3] += step[k];
    }
    if (missile->proc != MISSILE_PROC_PARABOLA && missile->kind != BULLET_KIND_GROUND) {
        missile->speed += missile->accel;
        if (missile->speed > missile->max_speed)
            missile->speed = missile->max_speed;
    }
    PSMTXInverse(missile->matrix, missile->inverse);
    if (missile->proc_delay < missile->update_count)
        misProc(missile);
    HSD_JObjSetTranslateX(missile->joint, missile->matrix[0][3]);
    HSD_JObjSetTranslateY(missile->joint, missile->matrix[1][3]);
    HSD_JObjSetTranslateZ(missile->joint, missile->matrix[2][3]);
    sMakeMatrix(missile->joint);
    missile->joint->matrix[0][0] = missile->matrix[0][0];
    missile->joint->matrix[0][1] = missile->matrix[0][1];
    missile->joint->matrix[0][2] = missile->matrix[0][2];
    missile->joint->matrix[0][3] = missile->matrix[0][3];
    missile->joint->matrix[1][0] = missile->matrix[1][0];
    missile->joint->matrix[1][1] = missile->matrix[1][1];
    missile->joint->matrix[1][2] = missile->matrix[1][2];
    missile->joint->matrix[1][3] = missile->matrix[1][3];
    missile->joint->matrix[2][0] = missile->matrix[2][0];
    missile->joint->matrix[2][1] = missile->matrix[2][1];
    missile->joint->matrix[2][2] = missile->matrix[2][2];
    missile->joint->matrix[2][3] = missile->matrix[2][3];
    sGlobal2Local(missile->joint);
    if (missile->beam_joints[0] != 0) {
        missile->beam_positions[0][0] = missile->matrix[0][3];
        missile->beam_positions[0][1] = missile->matrix[1][3];
        missile->beam_positions[0][2] = missile->matrix[2][3];
        missile->beam_joints[0]->matrix[0][0] = missile->joint->matrix[0][0];
        missile->beam_joints[0]->matrix[0][1] = missile->joint->matrix[0][1];
        missile->beam_joints[0]->matrix[0][2] = missile->joint->matrix[0][2];
        missile->beam_joints[0]->matrix[0][3] = missile->joint->matrix[0][3];
        missile->beam_joints[0]->matrix[1][0] = missile->joint->matrix[1][0];
        missile->beam_joints[0]->matrix[1][1] = missile->joint->matrix[1][1];
        missile->beam_joints[0]->matrix[1][2] = missile->joint->matrix[1][2];
        missile->beam_joints[0]->matrix[1][3] = missile->joint->matrix[1][3];
        missile->beam_joints[0]->matrix[2][0] = missile->joint->matrix[2][0];
        missile->beam_joints[0]->matrix[2][1] = missile->joint->matrix[2][1];
        missile->beam_joints[0]->matrix[2][2] = missile->joint->matrix[2][2];
        missile->beam_joints[0]->matrix[2][3] = missile->joint->matrix[2][3];
        sGlobal2Local(missile->beam_joints[0]);
        msFlyTrace(missile);
        for (k = 1; k < 7; k++) {
            if (missile->beam_joints[k] == 0)
                break;
        }
    }
    if (missile->light != 0) {
        position.x = missile->matrix[0][3];
        position.y = missile->matrix[1][3];
        position.z = missile->matrix[2][3];
        HSD_LObjSetPosition(missile->light, &position);
    }
}
