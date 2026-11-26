#pragma readonly_strings on
#include "zoid.h"
#include "missile.h"
#include "random.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

typedef f32 MisMtx[3][4];

extern ModelArchive *missileFile[130];
extern s32 nowMJ;
extern s32 misALL;
extern s32 sLightMis;
extern s32 SE_TableList[];
extern void ZeroMemory(void *dst, u32 size);
extern HSD_JObj *CopyJoint2(void *archive, s32 model);
extern HSD_JObj *searchJobjJoint(void *archive, HSD_JObj *joint, char *name);
extern void PSMTXRotRad(MisMtx m, char axis, f32 rad);
extern void PSMTXConcat(MisMtx a, MisMtx b, MisMtx ab);
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern struct HSD_LObj *LoadArc2Light(void *archive, s32 index);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

#pragma force_active on
static const char sMissilePathFormat[15] = "missile/%s.dat";
static const char sMissileLoadMessage[19] = "mis loa now // %s\n";
#pragma force_active off

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

void sMissileSet(ZoidState *owner, ZoidState *target_zoid, Missile *target_missile, MisMtx mtx, s32 bullet, s32 extra_damage)
{
    static s32 cc;
    Missile *missile;
    ModelArchive *archive;
    s32 i;
    s32 j;
    s32 k;
    s32 se_index;
    s32 se;
    MisMtx rot;
    f32 pad_stack;

    if (bullet <= 0)
        return;
    if (bullet >= 130)
        return;
    archive = missileFile[bullet];
    if (archive == NULL)
        return;
    if (archive->model_data == NULL)
        return;
    if (archive->models == NULL)
        return;
    nowMJ++;
    for (i = 0; i < 200; i++) {
        if (nowMJ >= 200)
            nowMJ = 0;
        missile = &missileStart[nowMJ];
        if (!(missile->flags & MISSILE_FLAG_ACTIVE))
            break;
        nowMJ++;
    }
    if (i == 200)
        return;
    if (missile->flags & MISSILE_FLAG_ACTIVE)
        return;
    misALL++;
    ZeroMemory(missile, sizeof(Missile));
    missile->hit_ground = 0;
    missile->bullet = bullet;
    missile->kind = Tea_bulletdat[bullet].kind;
    missile->zoid_hit = Tea_bulletdat[bullet].zoid_hit;
    missile->archive = archive;
    missile->joint = CopyJoint2(archive, 0);
    missile->beam_joints[0] = searchJobjJoint(archive, missile->joint, "beem_joint");
    if (missile->beam_joints[0] != NULL) {
        missile->beam_joints[1] = searchJobjJoint(archive, missile->joint, "to_beem_joint");
        missile->beam_joints[2] = searchJobjJoint(archive, missile->joint, "to_to_beem_joint");
        missile->beam_joints[3] = searchJobjJoint(archive, missile->joint, "to_to_to_beem_joint");
        missile->beam_joints[4] = searchJobjJoint(archive, missile->joint, "to_to_to_to_beem_joint");
        missile->beam_joints[5] = searchJobjJoint(archive, missile->joint, "to_to_to_to_to_beem_joint");
        missile->beam_joints[6] = searchJobjJoint(archive, missile->joint, "to_to_to_to_to_to_beem_joint");
    }
    missile->a1_joint = searchJobjJoint(archive, missile->joint, "a_1_joint");
    missile->owner = owner;
    if (owner != NULL)
        missile->owner_weapon_mount = owner->weapon_mount;
    missile->target_zoid = target_zoid;
    missile->target_missile = target_missile;
    missile->speed = 0.0f;
    missile->update_count = 0;
    missile->purge_timer = 0;
    missile->hit = 0;
    missile->flags = MISSILE_FLAG_ACTIVE;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            missile->matrix[i][j] = mtx[i][j];
    }
    PSMTXRotRad(rot, 'X', 3.1415926 * (2.0f * HSD_Randf()));
    PSMTXConcat(missile->matrix, rot, missile->matrix);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            missile->joint->matrix[i][j] = missile->matrix[i][j];
    }
    sGlobal2Local(missile->joint);
    HSD_JObjSetTranslateX(missile->joint, mtx[0][3]);
    HSD_JObjSetTranslateY(missile->joint, mtx[1][3]);
    HSD_JObjSetTranslateZ(missile->joint, mtx[2][3]);
    sMakeMatrix(missile->joint);
    for (i = 0; i < 7; i++) {
        if (missile->beam_joints[i] != NULL) {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 3; k++)
                    missile->beam_joints[i]->matrix[j][k] = mtx[j][k];
                missile->beam_joints[i]->matrix[j][3] = 0.1 * i + mtx[j][3];
                missile->beam_positions[i][j] = 0.1 * i + mtx[j][3];
            }
        }
    }
    for (i = 0; i < 7; i++) {
        if (missile->beam_joints[i] != NULL) {
            HSD_JObjSetScaleX(missile->beam_joints[i], 1.0f);
            sGlobal2Local(missile->beam_joints[i]);
        }
    }
    sMakeMatrix(missile->joint);
    missile->accel = 1.0f;
    missile->turn_rate = (f32)(Tea_bulletdat[bullet].turn_angle / 60.0) * 3.1415926 * 2.0 / 360.0;
    missile->max_speed = 0.1 * Tea_bulletdat[bullet].speed;
    {
        s32 procs[6] = { MISSILE_PROC_STRAIGHT, MISSILE_PROC_AT20, MISSILE_PROC_PARABOLA, MISSILE_PROC_FLOAT, MISSILE_PROC_GROUND, MISSILE_PROC_AT20 };
        missile->proc = procs[Tea_bulletdat[bullet].kind];
    }
    missile->proc_delay = 60;
    if (missile->proc == MISSILE_PROC_PARABOLA) {
        missile->speed = missile->max_speed;
        missile->proc_delay = 0;
    }
    if (missile->kind == BULLET_KIND_GROUND) {
        missile->speed = missile->max_speed;
        missile->proc_delay = 0;
        if (missile->speed < 1.0f)
            missile->speed = 1.0f;
    }
    if (owner->ai != NULL)
        owner->ai->missile_hit = 0;
    missile->damage = extra_damage + Tea_bulletdat[bullet].damage;
    sMissileSetAnim(missile, 0);
    sEffectSet(Tea_bulletdat[missile->bullet].fire_effect, 1, NULL, missile->joint, 0);
    se_index = Tea_bulletdat[bullet].se;
    se = -1;
    if (se_index >= 0)
        se = SE_TableList[se_index];
    missile->se = se;
    if (sLightMis != 0) {
        missile->light = LoadArc2Light(sEfctLight, cc + 1);
        cc++;
        if (cc >= 3)
            cc = 0;
    }
}
